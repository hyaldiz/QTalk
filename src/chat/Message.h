#pragma once

#include <QObject>

class Message : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString contents READ contents CONSTANT)
    Q_PROPERTY(QString time READ time CONSTANT)
    Q_PROPERTY(int recentChatID READ recentChatID CONSTANT)
public:
    explicit Message(const QString& contents, int recentChatID, QObject* parent = nullptr);

    const QString& contents() const;
    const QString& time() const;
    int recentChatID() const;

private:
    QString m_contents;
    QString m_time;
    int m_recentChatID;
};

Q_DECLARE_METATYPE(Message*)
