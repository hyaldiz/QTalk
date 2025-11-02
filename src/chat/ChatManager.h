#pragma once

#include <QObject>

#include "RecentChatList.h"
#include "RecentChatProxyList.h"

class ChatManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")

    Q_PROPERTY(RecentChatProxtList* recentChats READ recentChatProxtList CONSTANT)
public:
    explicit ChatManager(QObject* parent = nullptr);

    static ChatManager* instance();

    RecentChatList* recentChatList() const;

    RecentChat* openedChatRecentChat() const;
    void setOpenedChatRecentChat(RecentChat* newOpenedChatRecentChat);

    RecentChat* mainRecentChat() const;

    RecentChatProxtList* recentChatProxtList() const;

signals:
    void openedChatRecentChatChanged();
    void sendMessage(const QString& message);

public Q_SLOTS:
    void onSendMessage(const QString& message);

private:
    RecentChatList* m_recentChatList;
    RecentChatProxtList* m_recentChatProxyList;
    RecentChat* m_mainRecentChat;
    RecentChat* m_openedChatRecentChat;
};
