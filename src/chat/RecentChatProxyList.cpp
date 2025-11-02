#include "RecentChatProxyList.h"
#include "RecentChatList.h"

RecentChatProxtList::RecentChatProxtList(QObject* parent)
    : QSortFilterProxyModel(parent)
{
    setFilterRole(RecentChatList::RecentChatRoles::NameRole);
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setSortRole(RecentChatList::RecentChatRoles::NameRole);

    sort(0, Qt::AscendingOrder);
}

RecentChat *RecentChatProxtList::get(int index)
{
    if (index < 0 || index >= rowCount())
        return nullptr;

    QModelIndex modelIndex = this->index(index, 0);
    QModelIndex sourceIndex = mapToSource(modelIndex);
    return sourceModel()->data(sourceIndex, RecentChatList::RecentChatRoles::RecentChatObjectRole).value<RecentChat*>();
}
