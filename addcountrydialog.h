#ifndef ADDCOUNTRYDIALOG_H
#define ADDCOUNTRYDIALOG_H

#include <QDialog>
#include <QAbstractItemView>
#include "countriesmodel.h"
#include "country.h"
#include "countrymodel.h"

namespace Ui {
class AddCountryDialog;
}

class AddCountryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCountryDialog(CountriesModel *countriesModel, RegionModel *regionModel, QWidget *parent = nullptr);
    ~AddCountryDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddCountryDialog *ui;
    CountriesModel *_countriesModel;
    CountryModel *_newCountryModel;
    RegionModel *_regionModel;
    Country *_newCountry;
};

#endif // ADDCOUNTRYDIALOG_H
