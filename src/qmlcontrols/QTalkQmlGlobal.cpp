#include <QTalkQmlGlobal.h>

#include "QTKCorePlugin.h"
#include "QTKPalette.h"
#include "ChatManager.h"

QTalkQmlGlobal::QTalkQmlGlobal(QObject *parent)
    : QObject(parent)
    , m_corePlugin(QTKCorePlugin::instance())
    , m_palette(new QTKPalette(this))
    , m_chatManager(ChatManager::instance())
{

}

QTalkQmlGlobal::~QTalkQmlGlobal()
{

}

QString QTalkQmlGlobal::appName()
{
    return QCoreApplication::applicationName();
}

QString QTalkQmlGlobal::appVersion()
{
    QString versionStr = QCoreApplication::applicationVersion();
    if(QSysInfo::buildAbi().contains("32"))
    {
        versionStr += QStringLiteral(" %1").arg(tr("32 bit"));
    }
    else if(QSysInfo::buildAbi().contains("64"))
    {
        versionStr += QStringLiteral(" %1").arg(tr("64 bit"));
    }
    return versionStr;
}
