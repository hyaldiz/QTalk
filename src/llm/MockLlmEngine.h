#pragma once

#include "AbstractLLMEngine.h"

class MockLlmEngine : public AbstractLLMEngine
{
    Q_OBJECT
public:
    explicit MockLlmEngine(QObject* parent = nullptr);
    ~MockLlmEngine() override;

public slots:
    void loadModel(const QUrl &path, int nCtx, int nGpuLayers) override;
    void ask(const QString &userText) override;
    void stop() override;
    void unload() override;

public:
    void reset();

    void triggerModelLoaded();

    void triggerModelLoadFailed(const QString& errMsg);

    void triggerTokenReady(const QString& token);

    void triggerResponseFinished();

    void triggerError(const QString& errMsg);

    void simulateFullResponse(const QString& text);

    struct CallCounters {
        int loadModel = 0;
        int ask = 0;
        int stop = 0;
        int unload = 0;
    } calls;

    struct LastCallArgs {
        QUrl loadModelPath;
        int loadModelnCtx = 0;
        int loadModelnGpuLayers = 0;
        QString askUserText;
    } lastArgs;
};
