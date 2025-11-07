#include "UnitTest.h"
#include "QTKLoggingCategory.h"

#include <QtTest/QTest>

QTK_LOGGING_CATEGORY(UnitTestLog,"UnitTestLog")


UnitTest::UnitTest(QObject *parent)
    : QObject(parent)
{

}

UnitTest::~UnitTest()
{
    if(m_unitTestRun) {
        Q_ASSERT(m_initCalled);
        Q_ASSERT(m_cleanupCalled);
    }
}

void UnitTest::addTest(UnitTest* test)
{
    QList<UnitTest*>& tests = testList();

    Q_ASSERT(!tests.contains(test));

    tests.append(test);
}


QList<UnitTest *> &UnitTest::testList()
{
    static QList<UnitTest*> tests;
    return tests;
}

void UnitTest::init()
{
    m_initCalled = true;
}

void UnitTest::cleanup()
{
    m_cleanupCalled = true;

    QCoreApplication::processEvents();
}

int UnitTest::run(QStringView singleTest)
{
    int ret = 0;

    for(auto test: testList()) {
        if(singleTest.isEmpty() || singleTest == test->objectName()) {
            if(test->standalone() && singleTest.isEmpty()) {
                continue;
            }

            QStringList args;
            args << "*" << "-maxwarnings" << "0";
            ret += QTest::qExec(test, args);
        }
    }

    return ret;
}
