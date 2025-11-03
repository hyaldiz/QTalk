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
    Q_PROPERTY(bool writing READ writing WRITE setWriting NOTIFY writingChanged)
public:
    User(int id, const QString& name, QObject* parent = nullptr);

    int ID() const;
    const QString& name() const;
    ChatList* messages() const;
    bool writing() const;

    void setWriting(bool writing);

    void addMessage(Message* message);

signals:
    void messagesChanged();
    void writingChanged();

private:
    int m_ID;
    QString m_name;
    ChatList* m_messages;
    bool m_writing;
};
