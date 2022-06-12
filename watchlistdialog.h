#ifndef WATCHLISTDIALOG_H
#define WATCHLISTDIALOG_H

#include <QDialog>
#include "watchlistmodel.h"
#include "countrymodel.h"
#include "countrydialog.h"

namespace Ui {
class WatchlistDialog;
}

class WatchlistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WatchlistDialog(CountriesModel *mainModel,WatchlistModel *model, RatingModel *ratingModel,
                             RegionModel *regionModel, QWidget *parent = nullptr);
    ~WatchlistDialog();

private slots:
    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::WatchlistDialog *ui;
    CountriesModel *_mainModel;
    WatchlistModel *_watchlistModel;
    RatingModel *_ratingModel;
    RegionModel *_regionModel;
};

#endif // WATCHLISTDIALOG_H
