#include "RecentChat.h"

RecentChat::RecentChat(int id, const QString& name, QObject* parent)
    : QObject(parent)
    , m_ID(id)
    , m_name(name)
    , m_messages(new ChatList(this))
{

}

const QString &RecentChat::name() const
{
    return m_name;
}

int RecentChat::ID() const
{
    return m_ID;
}

void RecentChat::addMessage(Message *message)
{
    m_messages->append(message);
    emit messagesChanged();
}

ChatList *RecentChat::messages() const
{
    return m_messages;
}
