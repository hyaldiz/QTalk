#pragma once

#include <QQmlApplicationEngine>

class QTKApplicationPrivate
{
public:
    QTKApplicationPrivate()
        : m_qmlEngine(nullptr)
        , m_error(false)
    {

    }

    QQmlApplicationEngine* m_qmlEngine;    
    bool m_error;
};
