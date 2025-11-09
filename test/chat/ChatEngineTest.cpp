#include "ChatEngineTest.h"
#include "MockLlmEngine.h"
#include "ChatEngine.h"

#include <QtTest/QTest>
#include <QtTest/QSignalSpy>

void ChatEngineTest::init()
{
    m_mockEngine = new MockLlmEngine;

    m_chatEngine = new ChatEngine(m_mockEngine);
}

void ChatEngineTest::cleanup()
{
    delete m_chatEngine;

    m_chatEngine = nullptr;
}

void ChatEngineTest::test_loadModelSuccess()
{
    QSignalSpy spy_readyChanged(m_chatEngine,&ChatEngine::readyChanged);
    QSignalSpy spy_info(m_chatEngine,&ChatEngine::info);

    QCOMPARE(m_chatEngine->isModelReady(),false);

    m_chatEngine->load(QUrl("mock.gguf"), 2048, 99);

    m_mockEngine->triggerModelLoaded();

    QVERIFY(spy_readyChanged.wait(1000));

    QCOMPARE(m_mockEngine->calls.loadModel,1);
    QCOMPARE(m_mockEngine->lastArgs.loadModelPath, QUrl("mock.gguf"));

    QCOMPARE(spy_readyChanged.count(), 1);
    QCOMPARE(spy_readyChanged.last().at(0).toBool(),true);
    QCOMPARE(spy_info.last().at(0).toString(), QStringLiteral("Model ready"));
    QVERIFY(m_chatEngine->isModelReady());
}

void ChatEngineTest::test_sendWhenReadyForwardsToWorker()
{

}

void ChatEngineTest::test_sendWhenNotReadyEmitsInfo()
{

}

void ChatEngineTest::test_StopForwardsToWorker()
{

}
