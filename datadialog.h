#ifndef DATADIALOG_H
#define DATADIALOG_H

#include <QDialog>
#include "countriesmodel.h"

namespace Ui {
class DataDialog;
}

class DataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DataDialog(CountriesModel *model, QWidget *parent = nullptr);
    ~DataDialog();

private:
    Ui::DataDialog *ui;
    CountriesModel *_sourceModel;
};

#endif // DATADIALOG_H
