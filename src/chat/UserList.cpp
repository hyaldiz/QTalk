#include "UserList.h"

UserList::UserList(QObject* parent)
    : QAbstractListModel(parent)
{

}

const QList<User *> &UserList::users() const
{
    return m_users;
}

void UserList::setUsers(const QList<User *> &newUsers)
{
    if (m_users == newUsers)
        return;
    m_users = newUsers;
    emit usersChanged();
}

int UserList::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_users.count();
}

QVariant UserList::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_users.count())
        return QVariant();

    if (role == IDRole)
        return m_users[index.row()]->ID();
    else if (role == NameRole)
        return m_users[index.row()]->name();
    else if (role == UserObjectRole)
        return QVariant::fromValue(m_users[index.row()]);
    else
        return QVariant();
}

bool UserList::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() >= m_users.count())
        return false;

    return true;
}

QHash<int, QByteArray> UserList::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[IDRole] = "ID";
    roles[NameRole] = "name";
    roles[UserObjectRole] = "userObject";

    return roles;
}
