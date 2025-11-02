#pragma once

#include <QSortFilterProxyModel>
#include <QtQmlIntegration/QtQmlIntegration>

#include "RecentChat.h"

class RecentChatProxtList : public QSortFilterProxyModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")
public:
    explicit RecentChatProxtList(QObject* parent = nullptr);

    Q_INVOKABLE RecentChat* get(int index);
};
