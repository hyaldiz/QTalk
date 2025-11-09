#pragma once

#include <QObject>
#include <QLoggingCategory>

#include "AbstractLLMEngine.h"

Q_DECLARE_LOGGING_CATEGORY(LlamaLog)

#include <memory>

class LlamaEngine : public AbstractLLMEngine
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(LlamaEngine)

    friend class LlamaEnginePrivate;
public:
    explicit LlamaEngine(QObject* parent = nullptr);
    ~LlamaEngine() override;

public slots:
    void loadModel(const QUrl& path, int nCtx, int nGpuLayers) override;
    void ask(const QString& userText) override;
    void stop() override;
    void unload() override;

private:
    std::unique_ptr<class LlamaEnginePrivate> const d;
};
