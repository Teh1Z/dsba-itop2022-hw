#ifndef REGIONMODEL_H
#define REGIONMODEL_H

#include "region.h"
#include "country.h"
#include "countriesmodel.h"

#include <QAbstractTableModel>

class RegionModel : public QAbstractTableModel
{
public:
    RegionModel(const CountriesModel *allCountries);

    ~RegionModel();

    Region* getRegion(const QModelIndex &index) const;

    void del(Country *country);

    void addCountry(Country *country);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    std::vector<Region*>::const_iterator begin() const;
    std::vector<Region*>::const_iterator end() const;
private:
    std::vector<Region*> _regions;
};

#endif // REGIONMODEL_H
