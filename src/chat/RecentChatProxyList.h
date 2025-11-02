#pragma once

#include <QSortFilterProxyModel>

#include "RecentChat.h"

class RecentChatProxtList : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit RecentChatProxtList(QObject* parent = nullptr);

    Q_INVOKABLE RecentChat* get(int index);
};
