#include "ChatEngine.h"
#include "LlamaWorker.h"

#include <QMetaObject>

ChatEngine::ChatEngine(QObject* parent)
    : QObject(parent)
{
    m_worker = new LlamaWorker();
    m_worker->moveToThread(&m_thread);

    connect(&m_thread, &QThread::finished, m_worker, &QObject::deleteLater);

    connect(m_worker, &LlamaWorker::tokenReady, this, &ChatEngine::tokenArrived, Qt::QueuedConnection);
    connect(m_worker, &LlamaWorker::responseFinished, this, &ChatEngine::responseDone, Qt::QueuedConnection);

    connect(m_worker, &LlamaWorker::modelLoaded, this, [this]{
        m_ready = true;
        emit readyChanged(m_ready);
        emit info("Model ready");
    }, Qt::QueuedConnection);

    connect(m_worker, &LlamaWorker::modelLoadFailed, this, [this](const QString& e){
        m_ready = false;
        emit readyChanged(m_ready);
        emit error("Model load error: " + e);
    }, Qt::QueuedConnection);

    connect(m_worker, &LlamaWorker::error, this, [this](const QString& e){
        emit error("Error: " + e);
    }, Qt::QueuedConnection);

    m_thread.start();
}

ChatEngine::~ChatEngine() {
    if (m_worker) {
        QMetaObject::invokeMethod(m_worker, "stop", Qt::BlockingQueuedConnection);
        QMetaObject::invokeMethod(m_worker, "unload", Qt::BlockingQueuedConnection);
    }

    m_thread.quit();
    m_thread.wait();
}

void ChatEngine::load(const QUrl& modelPath, int nCtx, int nGpuLayers) {
    m_ready = false;
    emit readyChanged(m_ready);
    QMetaObject::invokeMethod(m_worker, "loadModel", Qt::QueuedConnection,
                              Q_ARG(QUrl, modelPath), Q_ARG(int, nCtx), Q_ARG(int, nGpuLayers));
}

void ChatEngine::send(const QString& text) {
    if (!m_ready) {
        emit info("Model not ready"); return;
    }

    QMetaObject::invokeMethod(m_worker, "ask", Qt::QueuedConnection, Q_ARG(QString, text));
}

void ChatEngine::stop() {
    //QMetaObject::invokeMethod(m_worker, "stop", Qt::QueuedConnection);

    m_worker->stop();
}

void ChatEngine::unload() {
    m_ready = false;
    emit readyChanged(m_ready);
    QMetaObject::invokeMethod(m_worker, "unload", Qt::QueuedConnection);
}
