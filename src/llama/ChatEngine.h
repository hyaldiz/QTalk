#pragma once

#include <QObject>
#include <QThread>
#include <QtQmlIntegration/QtQmlIntegration>

class LlamaWorker;

class ChatEngine : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")

    Q_PROPERTY(bool ready READ isModelReady NOTIFY readyChanged)
public:
    explicit ChatEngine(QObject* parent = nullptr);

    ~ChatEngine();

    Q_INVOKABLE void load(const QString& path, int nCtx = 2048, int nGpuLayers = 99);
    Q_INVOKABLE void send(const QString& text);
    Q_INVOKABLE void stop();
    Q_INVOKABLE void unload();

    bool isModelReady() const { return m_ready; }

signals:
    void tokenArrived(const QString& piece);
    void responseDone();
    void info(const QString& message);
    void error(const QString& message);
    void readyChanged(bool ready);

private:
    QThread m_thread;
    LlamaWorker* m_worker = nullptr;
    bool m_ready = false;
};
