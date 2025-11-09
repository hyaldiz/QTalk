#pragma once

#include <QObject>

#include "UserList.h"
#include "UserProxyList.h"

class ChatEngine;
class AbstractLLMEngine;

Q_MOC_INCLUDE("ChatEngine.h")

class ChatManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")

    Q_PROPERTY(User* openedChatUser READ openedChatUser WRITE setOpenedChatUser NOTIFY openedChatUserChanged)
    Q_PROPERTY(User* mainUser READ mainUser CONSTANT)
    Q_PROPERTY(ChatEngine* chatEngine READ chatEngine CONSTANT)
public:
    explicit ChatManager(QObject* parent = nullptr);

    void init(AbstractLLMEngine* llmEngine);

    static ChatManager* instance();

    UserList* userList() const;

    User* openedChatUser() const;
    void setOpenedChatUser(User* newOpenedUser);

    User* mainUser() const;

    UserProxyList* userProxyList() const;

    ChatEngine* chatEngine() const;

signals:
    void openedChatUserChanged();
    void sendMessage(const QString& message);

public Q_SLOTS:
    void onSendMessage(const QString& message);
    void onAsk(const QString& message);
    void onTokenArrived(const QString& piece);
    void onError(const QString& message);
    void onResponseDone();

    void stop();

private:
    UserList* m_userList;
    UserProxyList* m_userProxyList;
    User* m_mainUser;
    User* m_openedChatUser;

    ChatEngine* m_chatEngine;
    Message* m_lastMessage;
};
