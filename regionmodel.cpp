#include "regionmodel.h"

#include <map>

RegionModel::RegionModel(const CountriesModel *allCountries)
{
    std::map<QString, Region*> regions;
    Region *temp;
    for (auto country : *allCountries)
    {
        if (regions.count(country->region()) == 0)
        {
            temp = new Region(country->region());
            regions[country->region()] = temp;
            _regions.push_back(temp);
        }
        regions[country->region()]->addCountry(country);
    }
}

RegionModel::~RegionModel()
{
    for (auto &reg : _regions)
        delete reg;
}

Region* RegionModel::getRegion(const QModelIndex &index) const
{
    return _regions.at(index.row());
}

void RegionModel::del(Country *country)
{
    for (Region* region : _regions)
    {
        auto it = std::find(region->begin(), region->end(), country);
        if (it == region->end())
            continue;
        beginResetModel();
        region->erase(it);
        endResetModel();
    }
    emit layoutChanged();
}

void RegionModel::addCountry(Country *country)
{
    beginResetModel();
    for (Region* region : _regions)
    {
        if (country->region() == region->getName())
        {
            region->addCountry(country);
            return;
        }
    }
    Region *newRegion = new Region(country->region());
    newRegion->addCountry(country);
    _regions.push_back(newRegion);
    endResetModel();
    emit layoutChanged();
}

int RegionModel::rowCount(const QModelIndex &parent) const
{
    return _regions.size();
}

int RegionModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant RegionModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        const Region *region = _regions[index.row()];
        if (index.column() == 0)
            return region->getName();
        else
            return static_cast<unsigned long long>(region->getCases());
    }
    return {};
}

QVariant RegionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        RegionFields field = (RegionFields)section;

        switch (field)
        {
            case RegionFields::name:
                return "Regions";
            case RegionFields::cases:
                return "Number of cases";
            case RegionFields::COUNT:
                return {};
        }
    }
    return {};
}

std::vector<Region*>::const_iterator RegionModel::begin() const
{
    return _regions.begin();
}

std::vector<Region*>::const_iterator RegionModel::end() const
{
    return _regions.end();
}
