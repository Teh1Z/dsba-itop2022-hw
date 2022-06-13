#ifndef COUNTRIESMODEL_H
#define COUNTRIESMODEL_H

#include "country.h"
#include <QAbstractTableModel>


class CountriesModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    CountriesModel() = default;

    CountriesModel(const std::vector<Country> &data);

    ~CountriesModel() noexcept;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Country* getCountry(const QString &name);

    std::vector<Country*>& getAllCountries();

    void addCountry(Country* country);

    void del(const Country* country);

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation = Qt::Horizontal, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    Country* operator[](size_t &index) const;

    std::vector<Country*>::const_iterator begin() const;
    std::vector<Country*>::const_iterator end() const;

signals:
    void countryDeleted();

private:
    std::vector<Country*> _countries;
};

#endif // COUNTRIESMODEL_H
