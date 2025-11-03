#include "Message.h"

#include <QTime>

Message::Message(const QString& contents, int ID, QObject* parent)
    : QObject(parent)
    , m_contents(contents)
    , m_time(QTime::currentTime().toString("HH:mm"))
    , m_ID(ID)
{

}

const QString &Message::contents() const
{
    return m_contents;
}

const QString &Message::time() const
{
    return m_time;
}

int Message::ID() const
{
    return m_ID;
}
