#include "LlamaWorker_p.h"

LlamaWorkerPrivate::LlamaWorkerPrivate(LlamaWorker* qptr)
    : q(qptr)
    , model(nullptr)
    , ctx(nullptr)
    , smpl(nullptr)
    , vocab(nullptr)
    , cancel(false)
    , nCtx(2048)
    , nGpuLayers(0)
{

}

void LlamaWorkerPrivate::ensureSampler()
{
    if(smpl)
        return;

    llama_sampler* chain = llama_sampler_chain_init(llama_sampler_chain_default_params());
    llama_sampler_chain_add(chain, llama_sampler_init_min_p(0.05f,1));
    llama_sampler_chain_add(chain, llama_sampler_init_temp(0.8f));
    llama_sampler_chain_add(chain, llama_sampler_init_dist(LLAMA_DEFAULT_SEED));

    smpl = chain;
}

std::string LlamaWorkerPrivate::buildPromptFromChat(const std::string &user)
{
    if(!model)
        throw std::runtime_error("Model not exist");

    const char* tmpl = llama_model_chat_template(model, nullptr);

    messages.push_back({"user", strdup(user.c_str())});

    if(formatted.empty())
        formatted.assign(nCtx,0);

    int new_len = llama_chat_apply_template(
            tmpl,
            messages.data(),
            static_cast<int>(messages.size()),
            true,
            formatted.data(),
            static_cast<int>(formatted.size())
        );

    if(new_len > static_cast<int>(formatted.size())) {
        formatted.resize(new_len);

        new_len = llama_chat_apply_template(
            tmpl,
            messages.data(),
            static_cast<int>(messages.size()),
            true,
            formatted.data(),
            static_cast<int>(formatted.size())
        );
    }

    if(new_len < 0)
        throw std::runtime_error("Chat template not aplied");

    static int prev_len = 0;

    std::string prompt(formatted.begin() + prev_len, formatted.begin() + new_len);

    prev_len = llama_chat_apply_template(
            tmpl,
            messages.data(),
            static_cast<int>(messages.size()),
            false,
            nullptr,
            0
        );

    if(prev_len < 0)
        throw std::runtime_error("Chat template prev_len not fetched");

    return prompt;
}

void LlamaWorkerPrivate::clearMessages()
{
    for(auto& msg : messages) {
        if(msg.content)
            free(const_cast<char*>(msg.content));
    }

    messages.clear();
    formatted.clear();
}

void LlamaWorkerPrivate::unloadAll()
{
    if(smpl) {
        llama_sampler_free(smpl);
        smpl = nullptr;
    }

    if(ctx) {
        llama_free(ctx);
        ctx = nullptr;
    }

    if(model) {
        llama_model_free(model);
        model = nullptr;
    }

    vocab = nullptr;

    clearMessages();
}
