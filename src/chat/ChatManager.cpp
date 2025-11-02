#include "ChatManager.h"
#include "Message.h"

#include <QApplicationStatic>

Q_APPLICATION_STATIC(ChatManager, _chatManagerInstance)

ChatManager::ChatManager(QObject *parent) :
    QObject(parent),
    m_recentChatList(new RecentChatList(this)),
    m_recentChatProxyList(new RecentChatProxtList(this)),
    m_mainRecentChat(new RecentChat(0, "New chat", this)),
    m_openedChatRecentChat(Q_NULLPTR)
{
    connect(this, &ChatManager::sendMessage, this, &ChatManager::onSendMessage, Qt::QueuedConnection);

    m_recentChatProxyList->setSourceModel(m_recentChatList);
}

ChatManager *ChatManager::instance()
{
    return _chatManagerInstance();
}

RecentChatList *ChatManager::recentChatList() const
{
    return m_recentChatList;
}

RecentChat *ChatManager::openedChatRecentChat() const
{
    return m_openedChatRecentChat;
}

void ChatManager::setOpenedChatRecentChat(RecentChat *newOpenedChatRecentChat)
{
    if (m_openedChatRecentChat == newOpenedChatRecentChat)
        return;
    m_openedChatRecentChat = newOpenedChatRecentChat;
    emit openedChatRecentChatChanged();
}

RecentChat *ChatManager::mainRecentChat() const
{
    return m_mainRecentChat;
}

void ChatManager::onSendMessage(const QString &message)
{
    if(m_openedChatRecentChat == Q_NULLPTR)
        return;
    m_openedChatRecentChat->addMessage(new Message(message, m_mainRecentChat->ID(), m_openedChatRecentChat));
}

RecentChatProxtList *ChatManager::recentChatProxtList() const
{
    return m_recentChatProxyList;
}
