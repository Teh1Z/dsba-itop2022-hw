#include "region.h"

Region::Region(const QString &name) : _name(name) {}

void Region::addCountry(Country *country)
{
    _countries.push_back(country);
}

uint64_t Region::getCases() const
{
    uint64_t count = 0;
    for (auto &country : _countries)
    {
        count += country->confirmed();
    }

    return count;
}

QString Region::getName() const
{
    return _name;
}

std::vector<Country*> Region::getCountries() const
{
    return _countries;
}

std::vector<Country*>::const_iterator Region::begin() const
{
    return _countries.begin();
}

std::vector<Country*>::const_iterator Region::end() const
{
    return _countries.end();
}

void Region::erase(std::vector<Country*>::const_iterator it)
{
    _countries.erase(it);
}
