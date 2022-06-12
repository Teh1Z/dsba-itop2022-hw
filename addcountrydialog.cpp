#include "addcountrydialog.h"
#include "ui_addcountrydialog.h"

AddCountryDialog::AddCountryDialog(CountriesModel *countriesModel, RegionModel *regionModel, QWidget *parent) :
    _countriesModel(countriesModel),
    _regionModel(regionModel),
    QDialog(parent),
    ui(new Ui::AddCountryDialog)
{
    ui->setupUi(this);
    _newCountry = new Country();
    _newCountryModel = new CountryModel(_newCountry);
    ui->tableView->horizontalHeader()->setVisible(false);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
    ui->tableView->setModel(_newCountryModel);
}

AddCountryDialog::~AddCountryDialog()
{
    delete ui;
}

void AddCountryDialog::on_buttonBox_accepted()
{
    _countriesModel->addCountry(_newCountry);
    _regionModel->addCountry(_newCountry);
}

