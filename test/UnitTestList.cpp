#include "UnitTestList.h"
#include "UnitTest.h"

#include "ChatEngineTest.h"

namespace QTKUnitTest
{

int runTests(const QStringList &unitTests)
{
    UT_REGISTER_TEST(ChatEngineTest)

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

}
