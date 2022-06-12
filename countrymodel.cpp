#include "countrymodel.h"

CountryModel::CountryModel(Country* country, CountriesModel* mainModel, WatchlistModel* watchlistModel,
                           RatingModel* ratingModel, RegionModel *regionModel) :
    _country(country),
    _mainModel(mainModel),
    _watchlistModel(watchlistModel),
    _ratingModel(ratingModel),
    _regionModel(regionModel)
{}

int CountryModel::rowCount(const QModelIndex &parent) const
{
    return static_cast<int>(CountryFields::COUNT);
}

int CountryModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

Country* CountryModel::getCountry()
{
    return _country;
}

QString CountryModel::getName() const
{
    return _country->name();
}

void CountryModel::del()
{
    beginResetModel();
    _watchlistModel->del(_country);
    _ratingModel->del(_country);
    _regionModel->del(_country);
    _mainModel->del(_country);
    _country = nullptr;
    endResetModel();
    emit layoutChanged();
}

bool CountryModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    beginResetModel();
    _country->data[index.row()].setValue(value);
    endResetModel();
    emit layoutChanged();
    return true;
}

QVariant CountryModel::data(const QModelIndex &index, int role) const
{
    if (_country == nullptr) {
        return {};
    }
    if (_country->data.size() == 0)
        return {};
    else if (role == Qt::DisplayRole || role == Qt::EditRole)
        return _country->data[index.row()];

    return {};
}

QVariant CountryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Vertical)
    {
        CountryFields field = (CountryFields)section;

        switch (field)
        {
            case CountryFields::name:
                return "Country";
            case CountryFields::confirmed:
                return "Confirmed";
            case CountryFields::deaths:
                return  "Deaths";
            case CountryFields::recovered:
                return "Recovered";
            case CountryFields::active:
                return "Active";
            case CountryFields::newCases:
                return "New cases";
            case CountryFields::newDeaths:
                return "New deaths";
            case CountryFields::newRecovered:
                return "New recovered";
            case CountryFields::deathsPerCases:
                return "Deaths / 100 Cases";
            case CountryFields::recoveredPerCases:
                return "Recovered / 100 Cases";
            case CountryFields::deathsPerRecovered:
                return "Deaths / 100 Recovered";
            case CountryFields::confirmedWeek:
                return "Confirmed last week";
            case CountryFields::weekChange:
                return "1 week change";
            case CountryFields::weekIncrease:
                return "1 week % increase";
            case CountryFields::region:
                return "Region";
            case CountryFields::COUNT:
                return {};
        }
    }
    return {};
}

Qt::ItemFlags CountryModel::flags(const QModelIndex &index) const
{
    return {Qt::ItemIsEnabled | Qt::ItemIsEditable};
}
