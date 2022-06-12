#include "ratingmodel.h"

RatingModel::RatingModel(const std::vector<Country*> &countries, int ind) : _rating(countries), _index(ind) {}

int RatingModel::rowCount(const QModelIndex &parent) const
{
    return _rating.size();
}

int RatingModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

void RatingModel::changeIndex(int ind)
{
    beginResetModel();
    _index = ind;
    endResetModel();
    emit layoutChanged();
}

Country* RatingModel::getCountry(const QModelIndex &index) const
{
    return _rating[index.row()];
}

void RatingModel::del(const Country *country)
{
    auto it = std::find(_rating.begin(), _rating.end(), country);
    if (it == _rating.end())
        return;
    beginResetModel();
    _rating.erase(it);
    endResetModel();
    emit layoutChanged();
}

//void RatingModel::sort(int column, Qt::SortOrder order) {}

QVariant RatingModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        const Country *country = _rating[index.row()];
        if (index.column() == 0)
            return country->name();
        else
        {
            return country->data[_index];
        }

    }
    return {};
}

QVariant RatingModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Vertical)
    {
        return section + 1;
    }
    return {};
}

std::vector<Country*>::const_iterator RatingModel::begin() const
{
    return _rating.begin();
}

std::vector<Country*>::const_iterator RatingModel::end() const
{
    return _rating.end();
}
