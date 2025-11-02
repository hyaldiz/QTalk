#pragma once

#include <QObject>
#include <QVariant>

class QQmlApplicationEngine;

class QTKCorePlugin : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList appPages READ appPages CONSTANT)
public:
    explicit QTKCorePlugin(QObject* parent = nullptr);
    ~QTKCorePlugin();

    const QVariantList& appPages();

    static QTKCorePlugin* instance();

    virtual QQmlApplicationEngine* createQmlApplicationEngine(QObject* parent);

    virtual void createMainRootWindow(QQmlApplicationEngine* qmlEngine);
};
