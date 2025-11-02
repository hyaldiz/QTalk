#pragma once

#include <QApplication>
#include <QLoggingCategory>

#include <memory>

class QTKApplication;

#if defined(qApp)
#   undef qApp
#endif
#define qApp (static_cast<QTKApplication*>(QApplication::instance()))

#if defined(qGuiApp)
#   undef qGuiApp
#endif
#define qGuiApp (static_cast<QTKApplication*>(QGuiApplication::instance()))

#define qtalkApp() qApp

Q_DECLARE_LOGGING_CATEGORY(QTKApplicationLog)

class QTKApplication : public QApplication
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(QTKApplication)

    friend class QTKApplicationPrivate;
public:
    QTKApplication(int argc, char** argv);
    ~QTKApplication();

    void init();

private:
    QObject* rootQmlObject();
    void initCommon();

    std::unique_ptr<class QTKApplicationPrivate> const d;
};
