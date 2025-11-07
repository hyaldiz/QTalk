#pragma once

#include <QObject>
#include <QUrl>

class AbstractLLMEngine : public QObject
{
    Q_OBJECT
public:
    explicit AbstractLLMEngine(QObject* parent = nullptr)
        : QObject(parent)
    {

    }

    virtual ~AbstractLLMEngine() = default;

    virtual void loadModel(const QUrl& path, int nCtx, int nGpuLayers) = 0;

    virtual void ask(const QString& userText) = 0;

    virtual void stop() = 0;

    virtual void unload() = 0;

signals:
    void modelLoaded();
    void modelLoadFailed(const QString& error);
    void tokenReady(const QString& piece);
    void responseFinished();
    void error(const QString& message);
};
