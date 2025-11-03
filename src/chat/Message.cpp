#include "Message.h"

#include <QTime>

Message::Message(const QString& contents, int ID, QObject* parent)
    : QObject(parent)
    , m_contents(contents)
    , m_time(QTime::currentTime().toString("HH:mm"))
    , m_failed(false)
    , m_ID(ID)
{

}

void Message::appendToContents(const QString &piece)
{
    m_contents.append(piece);
    emit contentsChanged();
}

void Message::setFailed(bool failed)
{
    if(failed != m_failed) {
        m_failed = failed;
        emit failedChanged();
    }
}

const QString &Message::contents() const
{
    return m_contents;
}

const QString &Message::time() const
{
    return m_time;
}

bool Message::failed() const
{
    return m_failed;
}

int Message::ID() const
{
    return m_ID;
}
