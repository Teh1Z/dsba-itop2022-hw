#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "countriesmodel.h"
#include "countrymodel.h"
#include "csvparser.h"
#include "regionmodel.h"
#include "watchlistmodel.h"
#include "datadialog.h"
#include "logowidget.h"
#include "ratingmodel.h"
#include "addcountrydialog.h"
#include "aboutdialog.h"

#include <QMainWindow>
#include <QStandardItem>
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class SortModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

public slots:
    void resetCompleter();

    void slot_changed(const QModelIndex &lIndex, const QModelIndex &rIndex);

private slots:
    void on_actionOpen_File_triggered();

    void on_actionSave_File_triggered();

    void on_pushButton_clicked();

    void on_lineEdit_returnPressed();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_actionSave_File_As_triggered();

    void on_actionView_all_data_triggered();

    void on_tableView_2_doubleClicked(const QModelIndex &index);

    void on_actionAdd_country_triggered();

    void on_actionAbout_triggered();

private:
    void setupProxyModel();
    RegionModel *_allRegions = nullptr;
    CountriesModel *_allCountries = nullptr;
    WatchlistModel *_watchlistModel = nullptr;
    RatingModel *_ratingModel = nullptr;
    SortModel* _sorter;
    std::vector<QStandardItem*> _items = {};

    Ui::MainWindow *ui;
    logoWidget *logo;
    CSVParser _csvParser;
};


class SortModel : public QSortFilterProxyModel
{
public:
    SortModel(QObject* parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

#endif // MAINWINDOW_H
