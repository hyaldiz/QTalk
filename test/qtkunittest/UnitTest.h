#pragma once

#include <QObject>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(UnitTestLog)

#define UT_REGISTER_TEST(className) static UnitTestWrapper<className> className(#className, false);
#define UT_REGISTER_TEST_STANDALONE(className) static UnitTestWrapper<className> className(#className, true);

class UnitTest : public QObject
{
    Q_OBJECT
public:
    explicit UnitTest(QObject* parent = nullptr);
    virtual ~UnitTest();

    static int run(QStringView singleTest);

    bool standalone() const { return m_standalone; }
    void setStandalone(bool standalone) { m_standalone = standalone; }

    static void addTest(UnitTest* test);

protected slots:
    virtual void init();
    virtual void cleanup();

private:
    void unitTestCalled() { m_unitTestRun = true; }

    static QList<UnitTest*>& testList();

    bool m_unitTestRun = false;
    bool m_initCalled = false;
    bool m_cleanupCalled = false;
    bool m_standalone = false; //Only run specifically called from command line
};

template<class T>
class UnitTestWrapper
{
public:
    UnitTestWrapper(const QString& name, bool standalone)
        : m_unitTest(new T)
    {
        m_unitTest->setObjectName(name);
        m_unitTest->setStandalone(standalone);
        UnitTest::addTest(m_unitTest.data());
    }

private:
    QSharedPointer<T> m_unitTest;
};
