#define _LOG_CTOR_ACCESS_ public

#include "AppMessages.h"

#include <QDebug>
#include <QtConcurrent>
#include <QTextStream>

Q_GLOBAL_STATIC(AppLogModel,debug_model);

static QtMessageHandler old_handler;

static void msgHandler(QtMsgType type,const QMessageLogContext& context,const QString& msg)
{
    const char symbols[] = {'D','E','!','X','I'};
    QString output = QString("[%1]-[%2] %3").arg(symbols[type]).arg(QDateTime::currentDateTime().toString(Qt::ISODateWithMs)).arg(msg);

    if(!QString(context.category).startsWith("qt.quick")){
        debug_model->log(output);
    }

    if(old_handler != nullptr){
        old_handler(type,context,msg);
    }

    if(type == QtFatalMsg)
        abort();
}

void AppMessages::installHandler()
{
    old_handler = qInstallMessageHandler(msgHandler);

    // Force creation of debug model on installing thread
    Q_UNUSED(*debug_model)
}

AppLogModel::AppLogModel() : QStringListModel()
{
    Qt::ConnectionType contype = Qt::AutoConnection;
    connect(this, &AppLogModel::emitLog, this, &AppLogModel::threadSafeLog, contype);
}

AppLogModel::~AppLogModel()
{
    if(_logFile.isOpen())
        _logFile.close();
}

AppLogModel* AppMessages::getModel()
{
    return debug_model;
}

void AppLogModel::writeMessages(const QString dest_file)
{
    const QString writeBuffer(stringList().join('\n').append('\n'));

    QtConcurrent::run([dest_file,writeBuffer]
                      {
                          emit debug_model->writeStarted();
                          bool success = false;
                          QFile file(dest_file);
                          if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
                              QTextStream out(&file);
                              out << writeBuffer;
                              success = out.status() == QTextStream::Ok;
                          }
                          else{
                              qWarning() << "AppLogModel::writeMessages write failed:" << file.errorString();
                          }
                          emit debug_model->writeFinished();
                          Q_UNUSED(success)
                      });
}

void AppLogModel::log(const QString& message)
{
    emit debug_model->emitLog(message);
}

void AppLogModel::threadSafeLog(const QString& message)
{
    const int line = rowCount();
    insertRows(line,1);
    setData(index(line),message,Qt::DisplayRole);

    auto baseDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    QDir dir(baseDir);
    if (!dir.exists())
        dir.mkpath(QStringLiteral(".")); // baseDir'i oluştur

    QString saveFilePath = dir.filePath(QStringLiteral("QTKConsole.log"));

    if(_logFile.fileName().isEmpty()) {
        _logFile.setFileName(saveFilePath);
        if(!_logFile.open(QIODevice::WriteOnly | QIODevice::Text/* | QIODevice::Append*/)) {
            qWarning() << tr("Open console log output file failed %1 : %2").arg(_logFile.fileName()).arg(_logFile.errorString());
        }
    }

    if(_logFile.isOpen()){
        QTextStream out(&_logFile);
        out << message << "\n";
        _logFile.flush();
    }
}
