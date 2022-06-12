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

#include <QMainWindow>
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class FilterModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
//    Country &getCountryByIndex(QModelIndex index) const;

    void setCompleter (const std::vector<Country*> &data);
    ~MainWindow();

private slots:
    void on_actionOpen_File_triggered();

    void on_actionSave_File_triggered();

    void on_pushButton_clicked();

    void on_lineEdit_returnPressed();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_actionSave_File_As_triggered();

    void on_comboBox_currentIndexChanged(int index);

    void on_actionView_all_data_triggered();

    void on_tableView_2_doubleClicked(const QModelIndex &index);

    void on_actionAdd_country_triggered();

private:
    void setupProxyModel();
    QSortFilterProxyModel *_proxyModel = nullptr;
    RegionModel *_allRegions = nullptr;
    CountriesModel *_allCountries = nullptr;
    WatchlistModel *_watchlistModel = nullptr;
    RatingModel *_ratingModel = nullptr;
    FilterModel *_filterModel = nullptr;

    Ui::MainWindow *ui;
    logoWidget *logo;
    CSVParser _csvParser;
};

class FilterModel : public QSortFilterProxyModel
{
   Q_OBJECT
public:
  FilterModel (QObject *parent, const MainWindow *main_window);
protected:
//  virtual bool filterAcceptsRow (int source_row, const QModelIndex &parent) const override;
  virtual bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;
private:
  const MainWindow *main_window = nullptr;
};

#endif // MAINWINDOW_H
