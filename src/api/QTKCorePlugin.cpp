#include "QTKCorePlugin.h"
#include "QmlComponentInfo.h"

#include <QApplicationStatic>
#include <QQmlApplicationEngine>

Q_APPLICATION_STATIC(QTKCorePlugin, qtkCorePluginInstance)

QTKCorePlugin::QTKCorePlugin(QObject* parent)
    : QObject(parent)
{

}

QTKCorePlugin::~QTKCorePlugin()
{

}

QTKCorePlugin* QTKCorePlugin::instance()
{
    return qtkCorePluginInstance();
}

QQmlApplicationEngine* QTKCorePlugin::createQmlApplicationEngine(QObject* parent)
{
    QQmlApplicationEngine* const qmlEngine = new QQmlApplicationEngine(parent);
    qmlEngine->addImportPath("qrc:/qml");
    return qmlEngine;
}

void QTKCorePlugin::createMainRootWindow(QQmlApplicationEngine* qmlEngine)
{
    qmlEngine->load(QUrl(QStringLiteral("qrc:/qml/QTalk/MainRootWindow.qml")));
}

const QVariantList& QTKCorePlugin::appPages()
{
    static const QVariantList appList = {
        QVariant::fromValue(
            new QmlComponentInfo(
                tr("Example page 1"),
                QUrl::fromUserInput(QStringLiteral()),
                QUrl::fromUserInput(QStringLiteral())
            )
        )
    };

    return appList;
}
