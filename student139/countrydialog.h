#ifndef COUNTRYDIALOG_H
#define COUNTRYDIALOG_H

#include "countrymodel.h"
#include "countriesmodel.h"
#include "watchlistmodel.h"
#include "ratingmodel.h"

#include <QDialog>

namespace Ui {
class CountryDialog;
}

class CountryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CountryDialog(CountryModel *countryModel, WatchlistModel *watchlistModel, QWidget *parent = nullptr);
    ~CountryDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:

    Ui::CountryDialog *ui;
    CountryModel *_countryModel;
    WatchlistModel *_watchlistModel;
};

#endif // COUNTRYDIALOG_H
