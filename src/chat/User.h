#pragma once

#include <QObject>
#include <QtQmlIntegration/QtQmlIntegration>

#include "Message.h"
#include "ChatList.h"

class User : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")

    Q_PROPERTY(int ID READ ID CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(ChatList* messages READ messages CONSTANT FINAL)
public:
    User(int id, const QString& name, QObject* parent = nullptr);

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
