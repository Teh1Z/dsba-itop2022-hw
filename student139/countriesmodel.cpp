#include "countriesmodel.h"

CountriesModel::CountriesModel(const std::vector<Country*> &data) : _countries(data) {}

CountriesModel::~CountriesModel() noexcept
{
    for (Country* country : _countries)
    {
        delete country;
    }
}

int CountriesModel::rowCount(const QModelIndex &parent) const
{
    return _countries.size();
}

int CountriesModel::columnCount(const QModelIndex &parent) const
{
    return static_cast<int>(CountryFields::COUNT);
}

Country* CountriesModel::getCountry(const QString &name)
{
    for (Country* country : _countries)
    {
        if (country->name() == name)
            return country;
    }
    return nullptr;
}

std::vector<Country*>& CountriesModel::getAllCountries()
{
    return _countries;
}

void CountriesModel::addCountry(Country *country)
{
    beginResetModel();
    _countries.push_back(country);
    endResetModel();
    emit layoutChanged();
}

void CountriesModel::del(const Country* country)
{
    auto it = std::find(_countries.begin(), _countries.end(), country);
    if (it == _countries.end())
        return;
    beginResetModel();
    delete *it;
    _countries.erase(it);
    endResetModel();
    emit countryDeleted();
    emit layoutChanged();
}

bool CountriesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    beginResetModel();
    _countries[index.row()]->data[index.column()].setValue(value);
    endResetModel();
    emit layoutChanged();
    return true;
}

QVariant CountriesModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        const Country *country = _countries[index.row()];
        return country->data[index.column()];
    }
    return {};
}

QVariant CountriesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
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

Qt::ItemFlags CountriesModel::flags(const QModelIndex &index) const
{
    return {Qt::ItemIsEnabled | Qt::ItemIsEditable};
}

Country* CountriesModel::operator[](size_t &index) const
{
    return _countries[index];
}

std::vector<Country*>::const_iterator CountriesModel::begin() const
{
    return _countries.begin();
}

std::vector<Country*>::const_iterator CountriesModel::end() const
{
    return _countries.end();
}
