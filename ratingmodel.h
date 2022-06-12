#ifndef RATINGMODEL_H
#define RATINGMODEL_H

#include <QVariant>
#include <QAbstractTableModel>
#include "country.h"

class RatingModel : public QAbstractTableModel
{
public:
    RatingModel() = default;

    RatingModel(const std::vector<Country*> &countries, int ind = 1);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    void changeIndex(int ind);

    Country* getCountry(const QModelIndex &index) const;

    void del(const Country *country);

//    void sort(int column = 1, Qt::SortOrder order = Qt::DescendingOrder) override;

    QVariant data(const QModelIndex &index, int role = Qt::EditRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    std::vector<Country*>::const_iterator begin() const;
    std::vector<Country*>::const_iterator end() const;
private:
    int _index = 1;
    std::vector<Country*> _rating;
};

struct Comparator
{

};

#endif // RATINGMODEL_H
