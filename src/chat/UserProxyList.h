#pragma once

#include <QSortFilterProxyModel>
#include <QtQmlIntegration/QtQmlIntegration>

#include "User.h"

class UserProxyList : public QSortFilterProxyModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")
public:
    explicit UserProxyList(QObject* parent = nullptr);

    Q_INVOKABLE User* get(int index);
};
