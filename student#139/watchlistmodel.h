#ifndef WATCHLISTMODEL_H
#define WATCHLISTMODEL_H

#include "country.h"
#include <vector>
#include <QVariant>
#include <QAbstractTableModel>

class WatchlistModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    WatchlistModel() = default;

    void insertData(Country *country);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool contains(Country *country) const;

    Country* getCountry(QModelIndex &index) const;

    void del(const Country *country);

    void delByIndex(int &ind);

    std::vector<Country*>::const_iterator begin() const;
    std::vector<Country*>::const_iterator end() const;

private:
    std::vector<Country*> _watchList;
};

#endif // WATCHLISTMODEL_H
