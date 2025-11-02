#include "RecentChatList.h"

RecentChatList::RecentChatList(QObject* parent)
    : QAbstractListModel(parent)
{

}

const QList<RecentChat *> &RecentChatList::recentChats() const
{
    return m_recentChats;
}

void RecentChatList::setRecentChats(const QList<RecentChat *> &newRecentChats)
{
    if (m_recentChats == newRecentChats)
        return;
    m_recentChats = newRecentChats;
    emit recentChatsChanged();
}

int RecentChatList::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_recentChats.count();
}

QVariant RecentChatList::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_recentChats.count())
        return QVariant();

    if (role == IDRole)
        return m_recentChats[index.row()]->ID();
    else if (role == NameRole)
        return m_recentChats[index.row()]->name();
    else if (role == RecentChatObjectRole)
        return QVariant::fromValue(m_recentChats[index.row()]);
    else
        return QVariant();
}

bool RecentChatList::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() >= m_recentChats.count())
        return false;

    return true;
}

QHash<int, QByteArray> RecentChatList::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[IDRole] = "ID";
    roles[NameRole] = "name";
    roles[RecentChatObjectRole] = "recentChatObject";

    return roles;
}