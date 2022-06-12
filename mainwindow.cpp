#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "countrydialog.h"
#include "watchlistdialog.h"

#include <QCompleter>
#include <QFileDialog>
#include <QMessageBox>

#include <sstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    logo = new logoWidget(this);
//    _filterModel = new FilterModel(this, this);

    logo->setFixedSize(25, 25);
    ui->gridLayout_3->addWidget(logo, 0, 0);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableView_2->horizontalHeader()->setVisible(false);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    _allCountries = new CountriesModel();
    _proxyModel = new QSortFilterProxyModel();
    _watchlistModel = new WatchlistModel();
    _ratingModel = new RatingModel();
    _filterModel = new FilterModel(this, this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _allCountries;
    delete _allRegions;
    delete _watchlistModel;
    delete _ratingModel;
}

void MainWindow::setupProxyModel()
{
    _proxyModel->setSourceModel(_ratingModel);
    _proxyModel->sort(1, Qt::DescendingOrder);
    ui->tableView_2->setModel(_proxyModel);
}

FilterModel::FilterModel (QObject *parent, const MainWindow *main_window) : QSortFilterProxyModel (parent), main_window (main_window) {}

bool FilterModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{

}

void MainWindow::setCompleter (const std::vector<Country*> &data)
{
    QStringList wordList;

    for (size_t i = 0; i < data.size(); ++i)
        wordList.append(data[i]->data[0].toString());

    QCompleter* completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit->setCompleter(completer);
}



void MainWindow::on_actionOpen_File_triggered()
{
    const QString dir = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath(), "Dataset (*.csv)");
    if (!dir.size())
        return;
    auto data = _csvParser.read(dir);
    _allCountries = new CountriesModel(data);
    setCompleter(_allCountries->getAllCountries());

    ui->comboBox->clear();
    QStringList _fields = _csvParser.getHeaders();
    _fields.removeFirst();
    _fields.removeLast();
    ui->comboBox->addItems(_fields);

//    _allCountries = new CountriesModel(data);
    _allRegions = new RegionModel(_allCountries);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setModel(_allRegions);
}


void MainWindow::on_actionSave_File_triggered()
{
    _csvParser.write(_allCountries);
}


void MainWindow::on_actionSave_File_As_triggered()
{
    auto dir = QFileDialog::getSaveFileName (this, "Save File As", QDir::currentPath ());
    if (!dir.size ())
      return;

    _csvParser.write(_allCountries, dir);
}

void MainWindow::on_pushButton_clicked()
{
    WatchlistDialog watchlist_dialog(_allCountries, _watchlistModel, _ratingModel, _allRegions, this);
    watchlist_dialog.setWindowTitle("Watchlist");
    watchlist_dialog.exec();
}

void MainWindow::on_lineEdit_returnPressed()
{
    QString text = ui->lineEdit->text();
    Country* country = _allCountries->getCountry(text);
    if (country == nullptr)
    {
        QMessageBox::warning(this, "Search error", "Not found country: " + text);
        return;
    }
    CountryModel countryModel(country, _allCountries, _watchlistModel, _ratingModel, _allRegions);
    CountryDialog country_dialog(&countryModel, _watchlistModel, this);
    country_dialog.setWindowTitle("Country data");
    country_dialog.exec();
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    if (index.column() == 0)
    {
        Region* reg = _allRegions->getRegion(index);
        if (_ratingModel != nullptr)
            delete _ratingModel;

        _ratingModel = new RatingModel(reg->getCountries(), ui->comboBox->currentIndex() + 1);
        _filterModel->setSourceModel(_ratingModel);
        ui->tableView_2->setModel(_filterModel);

//        ui->tableView_2->setModel(_proxyModel);
//        ui->tableView_2->sortByColumn(2, Qt::DescendingOrder);

    }
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (_ratingModel != nullptr)
        _ratingModel->changeIndex(index + 1);
}

void MainWindow::on_actionView_all_data_triggered()
{
    DataDialog dataDialog(_allCountries, this);
    dataDialog.setWindowTitle("All data");
    dataDialog.exec();
}


void MainWindow::on_tableView_2_doubleClicked(const QModelIndex &index)
{
    if (index.column() == 0)
    {
        Country* country = _ratingModel->getCountry(index);
        CountryModel countryModel(country, _allCountries, _watchlistModel, _ratingModel, _allRegions);
        CountryDialog country_dialog(&countryModel, _watchlistModel);
        country_dialog.setWindowTitle("Country data");
        country_dialog.exec();
    }
}

void MainWindow::on_actionAdd_country_triggered()
{
    AddCountryDialog addCountry(_allCountries, _allRegions, this);
    addCountry.setWindowTitle("Add new Country");
    addCountry.exec();
}

