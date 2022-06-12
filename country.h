#ifndef COUNTRY_H
#define COUNTRY_H

#include <QVariant>
#include <vector>

enum class CountryFields
{
    name,
    confirmed,
    deaths,
    recovered,
    active,
    newCases,
    newDeaths,
    newRecovered,
    deathsPerCases,
    recoveredPerCases,
    deathsPerRecovered,
    confirmedWeek,
    weekChange,
    weekIncrease,
    region,

    COUNT
};

class Country
{
public:
    std::array<QVariant, static_cast<int>(CountryFields::COUNT)> data;

    Country(const std::array<QVariant, static_cast<int>(CountryFields::COUNT)> &data);

    Country() = default;

    QString getName();

    QString name() const;

    uint64_t confirmed() const;

    uint64_t deaths() const;

    uint64_t recovered() const;

    uint64_t active() const;

    uint64_t newCases() const;

    uint64_t newDeaths() const;

    uint64_t newRecovered() const;

    double deathsPerCases() const;

    double recoveredPerCases() const;

    double deathsPerRecovered() const;

    uint64_t confirmedWeek() const;

    uint64_t weekChange() const;

    double weekIncrease() const;

    QString region() const;
};

#endif // COUNTRY_H
