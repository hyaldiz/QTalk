#pragma once

#include <QObject>

#include "UserList.h"
#include "UserProxyList.h"

class ChatManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")

    Q_PROPERTY(User* openedChatUser READ openedChatUser WRITE setOpenedChatUser NOTIFY openedChatUserChanged)
    Q_PROPERTY(User* mainUser READ mainUser CONSTANT)

public:
    explicit ChatManager(QObject* parent = nullptr);

    static ChatManager* instance();

    UserList* userList() const;

    User* openedChatUser() const;
    void setOpenedChatUser(User* newOpenedUser);

    User* mainUser() const;

    UserProxyList* userProxyList() const;

signals:
    void openedChatUserChanged();
    void sendMessage(const QString& message);

public Q_SLOTS:
    void onSendMessage(const QString& message);

private:
    UserList* m_userList;
    UserProxyList* m_userProxyList;
    User* m_mainUser;
    User* m_openedChatUser;
};
