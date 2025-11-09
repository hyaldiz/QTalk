#pragma once

#include <QQmlApplicationEngine>

class QTKApplicationPrivate
{
public:
    QTKApplicationPrivate()
        : m_qmlEngine(nullptr)
        , m_runningUnitTests(false)
        , m_error(false)
    {

    }

    QQmlApplicationEngine* m_qmlEngine;
    bool m_runningUnitTests;
    bool m_error;
};
