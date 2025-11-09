#include "QTKApplication.h"
#include "QTKApplication_p.h"
#include "QTKCorePlugin.h"
#include "QTKLoggingCategory.h"
#include "ChatManager.h"
#include "LlamaEngine.h"

#include <QQmlApplicationEngine>

QTK_LOGGING_CATEGORY(QTKApplicationLog,"QTKApplicationLog")

QTKApplication::QTKApplication(int& argc, char** argv, CommandLineParser::Result& cli)
    : QApplication(argc,argv)
    , d(new QTKApplicationPrivate)
{
    d->m_runningUnitTests = cli.runningUnitTests;

    QString appName;

    if(d->m_runningUnitTests) {
        appName = QStringLiteral("%1_unittest").arg(QTK_APP_NAME);
    } else {
        appName = QTK_APP_NAME;
    }

    setApplicationName(QTK_APP_NAME);
    setApplicationVersion(QTK_APP_VERSION_STR);
}

QTKApplication::~QTKApplication()
{
    delete d->m_qmlEngine;
}

bool QTKApplication::runningUnitTests() const
{
    return d->m_runningUnitTests;
}

void QTKApplication::init()
{
    d->m_qmlEngine = QTKCorePlugin::instance()->createQmlApplicationEngine(this);

    connect(d->m_qmlEngine,&QQmlApplicationEngine::objectCreationFailed,this,&QCoreApplication::quit,Qt::QueuedConnection);

    QTKCorePlugin::instance()->createMainRootWindow(d->m_qmlEngine);

    if(!d->m_runningUnitTests)
        ChatManager::instance()->init(new LlamaEngine);
}

QObject* QTKApplication::rootQmlObject()
{
    if(d->m_qmlEngine && d->m_qmlEngine->rootObjects().size()) {
        return d->m_qmlEngine->rootObjects().at(0);
    }

    return nullptr;
}
