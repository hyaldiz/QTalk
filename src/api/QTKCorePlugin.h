#pragma once

#include <QObject>
#include <QVariant>
#include <QtQmlIntegration/QtQmlIntegration>
#include <QQmlApplicationEngine>

class QTKCorePlugin : public QObject
{
    Q_OBJECT
    QML_UNCREATABLE("")
    Q_PROPERTY(QVariantList appPages READ appPages CONSTANT)
    Q_PROPERTY(QString supportedLLMExtensions READ supportedLLMExtensions CONSTANT)
public:
    explicit QTKCorePlugin(QObject* parent = nullptr);
    ~QTKCorePlugin();

    const QVariantList& appPages();

    static QTKCorePlugin* instance();

    virtual QQmlApplicationEngine* createQmlApplicationEngine(QObject* parent);

    virtual void createMainRootWindow(QQmlApplicationEngine* qmlEngine);

    QString supportedLLMExtensions() const;
};
