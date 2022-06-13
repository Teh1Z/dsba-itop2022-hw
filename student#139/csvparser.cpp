#include "csvparser.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <fstream>
#include <sstream>

CSVParser::CSVParser() {}

std::vector<Country> CSVParser::read(const QString &dir)
{
    QFile file(dir);
    std::vector<Country> result;

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox msgBox;
        msgBox.setText("Could not open the file!");
        msgBox.setInformativeText(file.errorString());
        msgBox.exec();
    }

    _dir = dir;

    QTextStream inputStream(&file);

    QString line = inputStream.readLine();
    for (QString &word : line.split(','))
    {
        _headers.append(word);
        _columnsCount++;
    }

    do
    {
        Country row;
        QStringList wordList = inputStream.readLine().split(',');

        for (size_t i = 0; i < _columnsCount; ++i)
            row.data[i] = wordList[i];

        _rowsCount++;
        result.push_back(row);
    } while (!inputStream.atEnd());

    file.close();
    return result;
}

void CSVParser::write(const CountriesModel *model, const QString &dir)
{
    QString path = dir;

    if (!dir.size())
        path = _dir;

    QFile file(path);
    file.open(QIODevice::WriteOnly);
    QTextStream output(&file);

    _rowsCount = model->rowCount();
    _columnsCount = model->columnCount();

    for (size_t colId = 0; colId < _columnsCount; ++colId)
    {
        output << model->headerData(colId).toString();
        if (colId < _columnsCount - 1)
            output << ",";
    }
    output << "\n";

    for (size_t rowId = 0; rowId < _rowsCount; ++rowId)
    {
        for (size_t colId = 0; colId < _columnsCount; ++colId)
        {
            output << model->operator[](rowId)->data[colId].toString();
            if (colId < _columnsCount - 1)
                output << ",";
            else if (rowId < _rowsCount - 1)
                output << "\n";
        }
    }
    file.close();
}

const QStringList& CSVParser::getHeaders() const
{
    return _headers;
}

