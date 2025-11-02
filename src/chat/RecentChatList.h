#pragma once

#include <QAbstractListModel>

#include "RecentChat.h"

class RecentChatList : public QAbstractListModel
{
    Q_OBJECT
public:
    enum RecentChatRoles{
        IDRole = Qt::UserRole + 1,
        NameRole,
        RecentChatObjectRole
    };

    explicit RecentChatList(QObject* parent = nullptr);

    const QList<RecentChat*>& recentChats() const;
    void setRecentChats(const QList<RecentChat*> &newRecentChats);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QHash<int, QByteArray> roleNames() const;

signals:
    void recentChatsChanged();

private:
    QList<RecentChat*> m_recentChats;
};
