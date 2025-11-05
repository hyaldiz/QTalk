#include "QTKCorePlugin.h"
#include "QmlComponentInfo.h"

#include <QApplicationStatic>

Q_APPLICATION_STATIC(QTKCorePlugin, _qtkCorePluginInstance)

QTKCorePlugin::QTKCorePlugin(QObject* parent)
    : QObject(parent)
{

}

QTKCorePlugin::~QTKCorePlugin()
{

}

QTKCorePlugin* QTKCorePlugin::instance()
{
    return _qtkCorePluginInstance();
}

QQmlApplicationEngine* QTKCorePlugin::createQmlApplicationEngine(QObject* parent)
{
    auto qmlEngine = new QQmlApplicationEngine(parent);

    qmlEngine->addImportPath("qrc:/qml");

    return qmlEngine;
}

void QTKCorePlugin::createMainRootWindow(QQmlApplicationEngine* qmlEngine)
{
    qmlEngine->load(QUrl(QStringLiteral("qrc:/qml/QTalk/MainRootWindow.qml")));
}

QString QTKCorePlugin::supportedLLMExtensions() const
{
    QStringList extensions;
    extensions << "(*.gguf)";
    return extensions.join(',');
}

const QVariantList& QTKCorePlugin::appPages()
{
    static QVariantList appList;

    if(appList.isEmpty())
    {
        appList.append(QVariant::fromValue(
                new QmlComponentInfo(
                    tr("Example page 1"),
                    QUrl::fromUserInput(QStringLiteral()),
                    QUrl::fromUserInput(QStringLiteral())
                )
            ));
    }

    return appList;
}
