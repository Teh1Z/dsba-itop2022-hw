#include "ratingmodel.h"


RatingModel::RatingModel(const std::vector<Country*> &countries, QStringList headers,  std::vector<int> indexes)
    : _rating(countries), _headers(headers), _indexes(indexes) {}

int RatingModel::rowCount(const QModelIndex &parent) const
{
    return _rating.size();
}

int RatingModel::columnCount(const QModelIndex &parent) const
{
    return _indexes.size() + 1;
}

void RatingModel::changeIndexes(std::vector<int> indexes)
{
    beginResetModel();
    _indexes = indexes;
    endResetModel();
    emit layoutChanged();
}

void RatingModel::addIndex(int index)
{
    beginResetModel();
    _indexes.push_back(index);
    endResetModel();
    emit layoutChanged();
}

void RatingModel::delIndex(int index)
{
    auto it = std::find(_indexes.begin(), _indexes.end(), index);
    if (it == _indexes.end())
        return;
    beginResetModel();
    _indexes.erase(it);
    endResetModel();
    emit layoutChanged();
}

Country* RatingModel::getCountry(const QModelIndex &index) const
{
    return _rating[index.row()];
}

std::vector<Country*> RatingModel::getCountries()
{
    return _rating;
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

QVariant RatingModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        const Country *country = _rating[index.row()];
        if (index.column() == 0)
            return country->name();
        else
            return country->data[_indexes[index.column() - 1]];
    }
    else if (role == SortRole)
    {
        const Country *country = _rating[index.row()];
        if (index.column() == 0)
            return country->name();
        else
            return country->data[_indexes[index.column() - 1]].value<double>();
    }
    return {};
}

QVariant RatingModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        if (section == 0)
            return "Country";
        else
            return _headers[_indexes[section - 1]];
    }
    if (role == Qt::DisplayRole && orientation == Qt::Vertical)
        return section + 1;
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
