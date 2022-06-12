#include "country.h"

Country::Country(const std::array<QVariant, static_cast<int>(CountryFields::COUNT)> &data) : data(data) {}

QString Country::getName()
{
    return data[0].toString();
}

QString Country::name() const
{
    return data[(int)CountryFields::name].value<QString>();
}

uint64_t Country::confirmed() const
{
    return data[(int)CountryFields::confirmed].value<uint64_t>();
}

uint64_t Country::deaths() const
{
    return data[int(CountryFields::deaths)].value<uint64_t>();
}

uint64_t Country::recovered() const
{
    return data[int(CountryFields::recovered)].value<uint64_t>();
}

uint64_t Country::active() const
{
    return data[int(CountryFields::active)].value<uint64_t>();
}

uint64_t Country::newCases() const
{
    return data[int(CountryFields::newCases)].value<uint64_t>();
}

uint64_t Country::newDeaths() const
{
    return data[int(CountryFields::newDeaths)].value<uint64_t>();
}

uint64_t Country::newRecovered() const
{
    return data[int(CountryFields::newRecovered)].value<uint64_t>();
}

double Country::deathsPerCases() const
{
    return data[int(CountryFields::deathsPerCases)].value<double>();
}

double Country::recoveredPerCases() const
{
    return data[int(CountryFields::recoveredPerCases)].value<double>();
}

double Country::deathsPerRecovered() const
{
    return data[int(CountryFields::deathsPerRecovered)].value<double>();
}

uint64_t Country::confirmedWeek() const
{
    return data[int(CountryFields::confirmedWeek)].value<uint64_t>();
}

uint64_t Country::weekChange() const
{
    return data[int(CountryFields::weekChange)].value<uint64_t>();
}

double Country::weekIncrease() const
{
    return data[int(CountryFields::weekIncrease)].value<double>();
}

QString Country::region() const
{
    return data[int(CountryFields::region)].value<QString>();
}
