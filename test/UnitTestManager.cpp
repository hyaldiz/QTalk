#include "UnitTestManager.h"
#include "UnitTest.h"
#include "ChatEngineTest.h"

#include <QApplicationStatic>

Q_APPLICATION_STATIC(UnitTestManager, _unitTestManagerInstance)

UnitTestManager::UnitTestManager(QObject* parent)
    : QObject(parent)
{
    QTK_REGISTER_TEST(ChatEngineTest)
}

UnitTestManager::~UnitTestManager()
{

}

UnitTestManager *UnitTestManager::instance()
{
    return _unitTestManagerInstance;
}

int UnitTestManager::runTests(const QStringList &unitTests)
{
    int result = 0;
    int failures = 0;

    for(const auto& test: unitTests) {
        failures += UnitTest::run(test);
    }

    if(failures == 0) {
        qDebug() << "ALL TESTS PASSED";
        result = 0;
    } else {
        qWarning() << failures << " TESTS FAILED!";
        result = -failures;
    }

    return result;
}

void UnitTestManager::printRegisteredTests()
{
    const auto &tests = UnitTest::testList();

    qDebug() << "Registered unit tests:" << tests.size();

    for (UnitTest* test : tests) {
        const QString name = test->objectName().isEmpty()
                                 ? QString::fromLatin1(test->metaObject()->className())
                                 : test->objectName();

        qDebug()
            << "\t -" << name
            << "| standalone:" << (test->standalone() ? "true" : "false");
    }
}
