#include "countrydialog.h"
#include "ui_countrydialog.h"
#include "watchlistdialog.h"

#include <QMessageBox>

CountryDialog::CountryDialog(CountryModel *countryModel, WatchlistModel *watchlistModel, QWidget *parent) :
    _countryModel(countryModel),
    _watchlistModel(watchlistModel),
    QDialog(parent),
    ui(new Ui::CountryDialog)
{
    ui->setupUi(this);
    ui->label->setText(_countryModel->getCountry()->getName());
    ui->tableView->horizontalHeader()->setVisible(false);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(_countryModel);

    if (_watchlistModel->contains(_countryModel->getCountry()))
    {
        ui->pushButton->setEnabled(false);
        ui->pushButton->setText("Already added");
    }

//    connect(ui->tableView->itemDelegate(),SIGNAL(closeEditor(QWidget*,QAbstractItemDelegate::EndEditHint)),SLOT(on_cell_returnPressed()));
}

CountryDialog::~CountryDialog()
{
    delete ui;
}

void CountryDialog::on_pushButton_clicked()
{
    Country* country = _countryModel->getCountry();
    _watchlistModel->insertData(country);
    ui->pushButton->setEnabled(false);
    ui->pushButton->setText("Already added");
}

void CountryDialog::on_pushButton_2_clicked()
{
    this->close();
    _countryModel->del();
}


//void CountryDialog::on_tableView_activated(const QModelIndex &index)
//{
//    QMessageBox msgBox;
//    msgBox.setText("a");
//    msgBox.exec();
//}


//void CountryDialog::on_tableView_activated(const QModelIndex &index)
//{

//}

