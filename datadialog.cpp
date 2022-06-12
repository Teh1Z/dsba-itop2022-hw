#include "datadialog.h"
#include "ui_datadialog.h"

DataDialog::DataDialog(CountriesModel *model, QWidget *parent) :
    _sourceModel(model),
    QDialog(parent),
    ui(new Ui::DataDialog)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setModel(_sourceModel);
}

DataDialog::~DataDialog()
{
    delete ui;
}
