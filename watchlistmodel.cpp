#include "watchlistmodel.h"


void WatchlistModel::insertData(Country *country)
{
    _watchList.push_back(country);
    emit layoutChanged();
}

int WatchlistModel::rowCount(const QModelIndex &parent) const
{
    return _watchList.size();
}

int WatchlistModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant WatchlistModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        const Country *country = _watchList[index.row()];
        return country->name();
    }
    return {};
}

QVariant WatchlistModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return {};
}

bool WatchlistModel::contains(Country *country) const
{
    return std::count(_watchList.begin(), _watchList.end(), country) != 0;
}

Country* WatchlistModel::getCountry(QModelIndex &index) const
{
    return _watchList[index.row()];
}

void WatchlistModel::del(const Country *country)
{
    auto it = std::find(_watchList.begin(), _watchList.end(), country);
    if (it == _watchList.end())
        return;
    beginResetModel();
    _watchList.erase(it);
    endResetModel();
    emit layoutChanged();
}

void WatchlistModel::delByIndex(int &ind)
{
    _watchList.erase(_watchList.begin() + ind);
    emit layoutChanged();
}

std::vector<Country*>::const_iterator WatchlistModel::begin() const
{
    return _watchList.begin();
}

std::vector<Country*>::const_iterator WatchlistModel::end() const
{
    return _watchList.end();
}
