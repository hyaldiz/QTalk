#include "LlamaWorker.h"
#include "LlamaWorker_p.h"

#include <QThread>
#include <QDebug>

#include <cstdio>

LlamaWorker::LlamaWorker(QObject *parent)
    : QObject(parent)
    , d(new LlamaWorkerPrivate(this))
{

}

LlamaWorker::~LlamaWorker()
{
    d->cancel.store(true, std::memory_order_relaxed);
    d->unloadAll();
}

void LlamaWorker::unload()
{
    d->unloadAll();
}

void LlamaWorker::loadModel(const QString &path, int nCtx, int nGpuLayers)
{
    d->unloadAll();
    d->cancel = false;
    d->modelPath = path;
    d->nCtx = nCtx;
    d->nGpuLayers = nGpuLayers;

    llama_log_set([](ggml_log_level lvl, const char* text, void*) {
        if (lvl >= GGML_LOG_LEVEL_ERROR) std::fprintf(stderr, "%s", text);

        switch (static_cast<int>(lvl)) {
        case GGML_LOG_LEVEL_NONE:
        case GGML_LOG_LEVEL_DEBUG:
            qDebug() << text;
            break;
        case GGML_LOG_LEVEL_INFO:
            qInfo() << text;
            break;
        case GGML_LOG_LEVEL_WARN:
            qWarning() << text;
            break;
        case GGML_LOG_LEVEL_ERROR:
            qFatal() << text;
            break;
        }
    }, nullptr);

    ggml_backend_load_all();

    llama_model_params mp = llama_model_default_params();
    mp.n_gpu_layers = d->nGpuLayers;

    d->model = llama_model_load_from_file(path.toStdString().c_str(), mp);
    if(!d->model) {
        emit modelLoadFailed("Context not created");
        d->unloadAll();
        return;
    }

    d->vocab = llama_model_get_vocab(d->model);

    llama_context_params cp = llama_context_default_params();
    cp.n_ctx = d->nCtx;
    cp.n_batch = d->nCtx;

    d->ctx = llama_init_from_model(d->model,cp);
    if(!d->ctx) {
        emit modelLoadFailed("Context not created");
        d->unloadAll();
        return;
    }

    d->clearMessages();
    d->formatted.assign(d->nCtx, 0);

    emit modelLoaded();
}

void LlamaWorker::ask(const QString &userText)
{
    if (!d->ctx || !d->model) {
        emit error("Model not loaded");
        return;
    }

    d->cancel = false;
    d->ensureSampler();

    try {
        const std::string prompt = d->buildPromptFromChat(userText.toStdString());
        const bool is_first = llama_memory_seq_pos_max(llama_get_memory(d->ctx), 0) == -1;

        int n_prompt_tokens = -llama_tokenize(
            d->vocab,
            prompt.c_str(),
            static_cast<int>(prompt.size()),
            nullptr,
            0,
            is_first,
            true
            );

        if (n_prompt_tokens <= 0) {
            emit error("Tokenize error");
            emit responseFinished();
            return;
        }

        std::vector<llama_token> toks(n_prompt_tokens);

        if (llama_tokenize(d->vocab, prompt.c_str(), (int)prompt.size(),
                           toks.data(), (int)toks.size(), is_first, true) < 0) {
            emit error("Tokenize error");
            emit responseFinished();
            return;
        }

        llama_batch batch = llama_batch_get_one(toks.data(), static_cast<int>(toks.size()));
        llama_token new_id;

        while (!d->cancel.load(std::memory_order_relaxed)) {
            int n_ctx = llama_n_ctx(d->ctx);
            int n_ctx_used = llama_memory_seq_pos_max(llama_get_memory(d->ctx), 0) + 1;
            if ((n_ctx_used + batch.n_tokens) > n_ctx) {
                emit error("Context overflowed");
                break;
            }

            if (llama_decode(d->ctx, batch) != 0) {
                emit error("Decode error");
                break;
            }

            new_id = llama_sampler_sample(d->smpl, d->ctx, -1);
            if (llama_vocab_is_eog(d->vocab, new_id))
                break;

            char buf[256];
            int n = llama_token_to_piece(d->vocab, new_id, buf, sizeof(buf), 0, true);
            if (n < 0) {
                emit error("Token piece error");
                break;
            }

            emit tokenReady(QString::fromUtf8(buf, n));
            batch = llama_batch_get_one(&new_id, 1);

            // CPU'yu çok yormasın diye ufak bekleme (opsiyonel)
            // QThread::usleep(500);
        }

        emit responseFinished();
    }
    catch (const std::exception &e) {
        emit error(QString("Exception %1").arg(e.what()));
        emit responseFinished();
    }
}

void LlamaWorker::stop()
{
    d->cancel.store(true, std::memory_order_relaxed);
}
