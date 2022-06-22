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

    std::vector<Country*> read(const QString &dir);

    void write(const CountriesModel *model, const QString &dir = nullptr);

    const QStringList& getHeaders() const;
private:
    QString _dir;
    size_t _columnsCount = 0;
    size_t _rowsCount = 0;

    QStringList _headers;
};

#endif // CSVPARSER_H
