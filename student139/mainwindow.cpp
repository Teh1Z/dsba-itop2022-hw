#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "countrydialog.h"
#include "watchlistdialog.h"

#include <QCompleter>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardItemModel>

#include <sstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Corona data application");
    logo = new logoWidget(this);

    logo->setFixedSize(25, 25);
    ui->horizontalLayout_3->addWidget(logo, 0);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableView_2->setSortingEnabled(true);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);



    _allCountries = new CountriesModel();
    _watchlistModel = new WatchlistModel();
    _ratingModel = new RatingModel();

    _sorter = new SortModel(this);
    _sorter->sort(1, Qt::DescendingOrder);
    _sorter->setSortRole(RatingModel::SortRole);
    ui->tableView_2->setModel(_sorter);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _allCountries;
    delete _allRegions;
    delete _watchlistModel;
    delete _ratingModel;
}

void MainWindow::resetCompleter()
{
    QStringList wordList;
    for (auto country : *_allCountries)
        wordList.append(country->getName());
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

    connect(_allCountries, SIGNAL(countryDeleted()), this, SLOT(resetCompleter()));
    resetCompleter();

    ui->comboBox->clear();
    QStringList _fields = _csvParser.getHeaders();
    _fields.removeFirst();
    _fields.removeLast();

    QStandardItemModel *model = new QStandardItemModel(_fields.size(), 1);
    for (int i = 0; i < _fields.size(); ++i)
    {
        QStandardItem* item = new QStandardItem(_fields[i]);
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setData(Qt::Unchecked, Qt::CheckStateRole);
        _items.push_back(item);
        model->setItem(i, 0, item);
    }
    ui->comboBox->setModel(model);
    connect(model, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this,
            SLOT(slot_changed(const QModelIndex&, const QModelIndex&)));

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
    WatchlistDialog watchlistDialog(_allCountries, _watchlistModel, _ratingModel, _allRegions, this);
    watchlistDialog.exec();
}

void MainWindow::on_lineEdit_returnPressed()
{
    QString text = ui->lineEdit->text();
    Country* country = _allCountries->getCountry(text);
    ui->lineEdit->clear();
    if (country == nullptr)
    {
        QMessageBox::warning(this, "Search error", "Not found country: " + text);
        return;
    }
    CountryModel countryModel(country, _allCountries, _watchlistModel, _ratingModel, _allRegions);
    CountryDialog countryDialog(&countryModel, _watchlistModel);
    countryDialog.exec();
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    if (index.column() == 0)
    {
        Region* reg = _allRegions->getRegion(index);
        if (_ratingModel != nullptr)
            delete _ratingModel;

        QStringList _fields = _csvParser.getHeaders();
        _fields.removeFirst();
        _fields.removeLast();
        _ratingModel = new RatingModel(reg->getCountries(), _fields);
        _sorter->setSourceModel(_ratingModel);
    }
}

void MainWindow::on_actionView_all_data_triggered()
{
    DataDialog dataDialog(_allCountries, this);
    dataDialog.exec();
}

void MainWindow::on_tableView_2_doubleClicked(const QModelIndex &index)
{
    if (index.column() == 0)
    {
        Country* country = _ratingModel->getCountry(_sorter->mapToSource(index));
        CountryModel countryModel(country, _allCountries, _watchlistModel, _ratingModel, _allRegions);
        CountryDialog countryDialog(&countryModel, _watchlistModel);
        countryDialog.exec();
    }
}

void MainWindow::on_actionAdd_country_triggered()
{
    AddCountryDialog addCountry(_allCountries, _allRegions, this);
    connect(&addCountry, SIGNAL(countryAdded()), this, SLOT(resetCompleter()));
    addCountry.exec();
}

SortModel::SortModel(QObject* parent) : QSortFilterProxyModel(parent) {}

QVariant SortModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical && role == Qt::DisplayRole)
        return section + 1;
    return QSortFilterProxyModel::headerData(section, orientation, role);
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog aboutDialog(this);
    aboutDialog.exec();
}

void MainWindow::slot_changed(const QModelIndex& lIndex, const QModelIndex& rIndex)
{
    QStandardItem* item = _items[lIndex.row()];
    if (item->checkState() == Qt::Checked)
        _ratingModel->addIndex(lIndex.row());
    else
        _ratingModel->delIndex(lIndex.row());
}
