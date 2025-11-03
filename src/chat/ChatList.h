#pragma once

#include <QAbstractListModel>

#include "Message.h"

class ChatList : public QAbstractListModel
{
    Q_OBJECT

    using Messages_t = QList<Message*>;
public:
    enum ChatRoles {
        IDRole = Qt::UserRole + 1,
        ContentsRole,
        TimeRole,
        FailedRole
    };

    explicit ChatList(QObject* parent = nullptr);

    int count() const;
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    void append(Message* message);
    Q_INVOKABLE Message* at(int index) const;

signals:
    void countChanged();

private:
    Messages_t m_messages;
};
