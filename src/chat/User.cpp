#include "User.h"

User::User(int id, const QString& name, QObject* parent)
    : QObject(parent)
    , m_ID(id)
    , m_name(name)
    , m_messages(new ChatList(this))
    , m_writing(false)
{

}

const QString &User::name() const
{
    return m_name;
}

int User::ID() const
{
    return m_ID;
}

void User::addMessage(Message *message)
{
    m_messages->append(message);
    emit messagesChanged();
}

ChatList *User::messages() const
{
    return m_messages;
}

bool User::writing() const
{
    return m_writing;
}

void User::setWriting(bool writing)
{
    if(writing != m_writing) {
        m_writing = writing;
        emit writingChanged();
    }
}
