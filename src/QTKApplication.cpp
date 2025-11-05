#include "QTKApplication.h"
#include "QTKApplication_p.h"
#include "QTKCorePlugin.h"
#include "QTKLoggingCategory.h"

#include <QQmlApplicationEngine>

QTK_LOGGING_CATEGORY(QTKApplicationLog,"QTKApplicationLog")

QTKApplication::QTKApplication(int argc, char** argv)
    : QApplication(argc,argv)
    , d(new QTKApplicationPrivate)
{
    setApplicationName(QTK_APP_NAME);
    setApplicationVersion(QString(QTK_APP_VERSION_STR));
}

QTKApplication::~QTKApplication()
{

}

void QTKApplication::init()
{
    d->m_qmlEngine = QTKCorePlugin::instance()->createQmlApplicationEngine(this);

    connect(d->m_qmlEngine,&QQmlApplicationEngine::objectCreationFailed,this,&QCoreApplication::quit,Qt::QueuedConnection);

    QTKCorePlugin::instance()->createMainRootWindow(d->m_qmlEngine);
}

QObject* QTKApplication::rootQmlObject()
{
    if(d->m_qmlEngine && d->m_qmlEngine->rootObjects().size()) {
        return d->m_qmlEngine->rootObjects().at(0);
    }

    return nullptr;
}
