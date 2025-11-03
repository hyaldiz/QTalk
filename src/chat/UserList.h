#pragma once

#include <QAbstractListModel>

#include "User.h"

class UserList : public QAbstractListModel
{
    Q_OBJECT
public:
    enum UserRoles{
        IDRole = Qt::UserRole + 1,
        NameRole,
        UserObjectRole
    };

    explicit UserList(QObject* parent = nullptr);

    const QList<User*>& users() const;
    void setUsers(const QList<User*> &newUsers);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QHash<int, QByteArray> roleNames() const;

signals:
    void usersChanged();

private:
    QList<User*> m_users;
};
