#pragma once

#include <QObject>
#include <QStringListModel>
#include <QFile>
#include <QUrl>

#ifndef _LOG_CTOR_ACCESS_
#define _LOG_CTOR_ACCESS_ private
#endif

class AppLogModel : public QStringListModel
{
    Q_OBJECT
public:
    Q_INVOKABLE void writeMessages(const QString dest_file);

    static void log(const QString& message);

signals:
    void emitLog(const QString message);
    void writeStarted();
    void writeFinished();

private slots:
    void threadSafeLog(const QString& message);

private:
    QFile _logFile;

    _LOG_CTOR_ACCESS_:
                        AppLogModel();
    ~AppLogModel();
};

class AppMessages
{
public:
    static void installHandler();
    static AppLogModel* getModel();
};
