#include "ChatList.h"

ChatList::ChatList(QObject* parent)
    : QAbstractListModel(parent)
{

}

int ChatList::count() const
{
    return m_messages.count();
}

int ChatList::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_messages.count();
}

QVariant ChatList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    Message* message = m_messages.at(index.row());

    if (role == IDRole)
        return message->ID();
    else if (role == TimeRole)
        return message->time();
    else if (role == ContentsRole)
        return message->contents();
    else if(role == FailedRole)
        return message->failed();
    else
        return QVariant();
}

QHash<int, QByteArray> ChatList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IDRole] = "ID";
    roles[TimeRole] = "time";
    roles[ContentsRole] = "contents";
    roles[FailedRole] = "failed";

    return roles;
}

void ChatList::append(Message *message)
{
    beginInsertRows(QModelIndex(), m_messages.count(), m_messages.count());
    m_messages.append(message);

    connect(message, &Message::contentsChanged, this, [this,message](){
        const int r = m_messages.indexOf(message);
        if(r >= 0) {
            QModelIndex idx = index(r, 0);
            emit dataChanged(idx, idx, {ContentsRole});
        }
    });

    connect(message, &Message::failedChanged, this, [this,message](){
        const int r = m_messages.indexOf(message);
        if(r >= 0) {
            QModelIndex idx = index(r, 0);
            emit dataChanged(idx, idx, {FailedRole});
        }
    });

    endInsertRows();

    emit countChanged();
}

Message *ChatList::at(int index) const
{
    if (index < 0 || index >= m_messages.count())
        return nullptr;

    return m_messages.at(index);
}
