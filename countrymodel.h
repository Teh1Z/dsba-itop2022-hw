#ifndef COUNTRYMODEL_H
#define COUNTRYMODEL_H

#include <QAbstractTableModel>
#include <country.h>
#include "countriesmodel.h"
#include "watchlistmodel.h"
#include "ratingmodel.h"
#include "regionmodel.h"

class CountryModel : public QAbstractTableModel
{
public:
    CountryModel() = default;

    CountryModel(Country* country, CountriesModel* mainModel = nullptr, WatchlistModel* watchListModel = nullptr,
                 RatingModel* ratingModel = nullptr, RegionModel *regionModel = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Country* getCountry();

    QString getName() const;

    void chageData();

    void del();

//    void setData(const std::vector<Country> &data);

//    void setData(const Country &data);

//    void deleteData(int ind);

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    QVariant data(const QModelIndex &index, int role = Qt::EditRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
private:
    Country *_country;
    CountriesModel *_mainModel;
    WatchlistModel *_watchlistModel;
    RatingModel *_ratingModel;
    RegionModel *_regionModel;
};

#endif // COUNTRYMODEL_H
