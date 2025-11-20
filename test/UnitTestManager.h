#pragma once

#include <QObject>

class UnitTestManager : public QObject
{
    Q_OBJECT
public:
    explicit UnitTestManager(QObject* parent = nullptr);
    ~UnitTestManager();

    static UnitTestManager* instance();

    virtual int runTests(const QStringList& unitTests);

    void printRegisteredTests();
};
