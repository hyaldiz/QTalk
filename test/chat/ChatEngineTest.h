#include "UnitTest.h"

class ChatEngineTest : public UnitTest
{
    Q_OBJECT
private slots:
    void test_loadModelSuccess();
    void test_sendWhenReadyForwardsToWorker();
    void test_sendWhenNotReadyEmitsInfo();
    void test_StopForwardsToWorker();

protected:
    void init() final;
    void cleanup() final;

private:
    class MockLlmEngine* m_mockEngine = nullptr;
    class ChatEngine* m_chatEngine = nullptr;
};
