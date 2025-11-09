#include "MockLlmEngine.h"

MockLlmEngine::MockLlmEngine(QObject *parent)
    : AbstractLLMEngine(parent)
{
    reset();
}

MockLlmEngine::~MockLlmEngine()
{

}

void MockLlmEngine::loadModel(const QUrl &path, int nCtx, int nGpuLayers)
{
    calls.loadModel++;
    lastArgs.loadModelPath = path;
    lastArgs.loadModelnCtx = nCtx;
    lastArgs.loadModelnGpuLayers = nGpuLayers;
}

void MockLlmEngine::ask(const QString &userText)
{
    calls.ask++;
    lastArgs.askUserText = userText;
}

void MockLlmEngine::stop()
{
    calls.stop++;
}

void MockLlmEngine::unload()
{
    calls.unload++;
}

void MockLlmEngine::reset()
{
    calls = {};
    lastArgs = {};
}

void MockLlmEngine::triggerModelLoaded()
{
    emit modelLoaded();
}

void MockLlmEngine::triggerModelLoadFailed(const QString &errMsg)
{
    emit modelLoadFailed(errMsg);
}

void MockLlmEngine::triggerTokenReady(const QString &token)
{
    emit tokenReady(token);
}

void MockLlmEngine::triggerResponseFinished()
{
    emit responseFinished();
}

void MockLlmEngine::triggerError(const QString &errMsg)
{
    emit error(errMsg);
}

void MockLlmEngine::simulateFullResponse(const QString &text)
{
    QStringList parts = text.split(' ',Qt::SkipEmptyParts);
    for(const auto& part: parts) {
        emit tokenReady(part + " ");
    }

    emit responseFinished();
}
