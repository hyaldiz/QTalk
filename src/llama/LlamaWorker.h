#pragma once

#include <QObject>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(LlamaLog)

#include <memory>

class LlamaWorker : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(LlamaWorker)

    friend class LlamaWorkerPrivate;
public:
    explicit LlamaWorker(QObject* parent = nullptr);
    ~LlamaWorker() override;

public slots:
    void loadModel(const QString& path, int nCtx, int nGpuLayers);
    void ask(const QString& userText);
    void stop();
    void unload();

signals:
    void modelLoaded();
    void modelLoadFailed(const QString& error);
    void tokenReady(const QString& piece);
    void responseFinished();
    void error(const QString& message);

private:
    std::unique_ptr<class LlamaWorkerPrivate> const d;
};
