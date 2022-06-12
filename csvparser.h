#ifndef CSVPARSER_H
#define CSVPARSER_H

#include "country.h"
#include "countriesmodel.h"

#include <QString>
#include <vector>

class CSVParser
{
public:
    CSVParser();

    QString getPath() const;

    std::vector<Country> read(const QString &dir);

    void write(const CountriesModel *model, const QString &dir = nullptr);

    const QStringList& getHeaders() const;

//    size_t getColumnIndex(const std::string& columnName);

    size_t getColumnsCount() const;

    size_t getRowsCount() const;

//    std::vector<Country> getData();

//    size_t findFirst(const std::vector<QString>& querry) const;

    QStringList& operator[](const size_t idx);

    QStringList operator [](const size_t idx) const;
private:
    QString _dir;
    size_t _columnsCount = 0;
    size_t _rowsCount = 0;

    QStringList _headers;
    std::vector<QStringList> _table;
};

#endif // CSVPARSER_H
