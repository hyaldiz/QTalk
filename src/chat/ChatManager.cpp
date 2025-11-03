#include "ChatManager.h"
#include "Message.h"
#include "ChatEngine.h"

#include <QApplicationStatic>

Q_APPLICATION_STATIC(ChatManager, _chatManagerInstance)

ChatManager::ChatManager(QObject *parent)
    : QObject(parent)
    , m_userList(new UserList(this))
    , m_userProxyList(new UserProxyList(this))
    , m_mainUser(new User(0, "MeAndYou", this))
    , m_openedChatUser(new User(1,"LLMModel", this))
    , m_chatEngine(new ChatEngine(this))

{
    connect(this, &ChatManager::sendMessage, this, &ChatManager::onSendMessage, Qt::QueuedConnection);
    connect(this, &ChatManager::sendMessage, this, &ChatManager::askHandler, Qt::QueuedConnection);

    m_userProxyList->setSourceModel(m_userList);
}

ChatManager *ChatManager::instance()
{
    return _chatManagerInstance();
}

UserList *ChatManager::userList() const
{
    return m_userList;
}

User *ChatManager::openedChatUser() const
{
    return m_openedChatUser;
}

void ChatManager::setOpenedChatUser(User* newOpenedChatUser)
{
    if (m_openedChatUser == newOpenedChatUser)
        return;
    m_openedChatUser = newOpenedChatUser;
    emit openedChatUserChanged();
}

User *ChatManager::mainUser() const
{
    return m_mainUser;
}

void ChatManager::onSendMessage(const QString &message)
{
    if(m_openedChatUser == Q_NULLPTR)
        return;
    m_openedChatUser->addMessage(new Message(message, m_mainUser->ID(), m_openedChatUser));
}

void ChatManager::askHandler(const QString &message)
{
    m_chatEngine->send("Merhaba");
}

UserProxyList *ChatManager::userProxyList() const
{
    return m_userProxyList;
}
