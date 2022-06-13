#include "watchlistdialog.h"
#include "ui_watchlistdialog.h"

WatchlistDialog::WatchlistDialog(CountriesModel *mainModel, WatchlistModel *watchlistModel,
                                 RatingModel *ratingModel, RegionModel *regionModel, QWidget *parent) :
    _mainModel(mainModel),
    _watchlistModel(watchlistModel),
    _ratingModel(ratingModel),
    _regionModel(regionModel),
    QDialog(parent),
    ui(new Ui::WatchlistDialog)
{
    ui->setupUi(this);
    setWindowTitle("Watchlist");
    if (_watchlistModel->rowCount() == 0)
        ui->pushButton->setEnabled(false);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setVisible(false);
    ui->tableView->setModel(_watchlistModel);
}

WatchlistDialog::~WatchlistDialog()
{
    delete ui;
}

void WatchlistDialog::on_tableView_doubleClicked(const QModelIndex &index)
{
    QModelIndex ind = ui->tableView->currentIndex();
    Country* country = _watchlistModel->getCountry(ind);
    CountryModel countryModel(country, _mainModel, _watchlistModel, _ratingModel, _regionModel);
    CountryDialog country_dialog(&countryModel, _watchlistModel, this);
    country_dialog.setWindowTitle("Country data");
    country_dialog.exec();
}


void WatchlistDialog::on_pushButton_clicked()
{
    int ind = ui->tableView->selectionModel()->currentIndex().row();
    _watchlistModel->delByIndex(ind);
}
