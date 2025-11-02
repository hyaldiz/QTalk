#pragma once

#include <QObject>

#include "Message.h"
#include "ChatList.h"

class RecentChat : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int ID READ ID CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
public:
    RecentChat(int id, const QString& name, QObject* parent = nullptr);

    int ID() const;
    const QString& name() const;

    void addMessage(Message* message);

    ChatList* messages() const;

signals:
    void messagesChanged();

private:
    int m_ID;
    QString m_name;
    ChatList* m_messages;
};
