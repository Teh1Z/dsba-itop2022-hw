#ifndef REGION_H
#define REGION_H

#include "country.h"
#include <map>

enum class RegionFields
{
    name,
    cases,

    COUNT
};

class Region
{
public:
    Region() = default;

    Region(const QString &name);

    void addCountry(Country* country);

    uint64_t getCases() const;

    QString getName() const;

    std::vector<Country*> getCountries() const;

    std::vector<Country*>::const_iterator begin() const;
    std::vector<Country*>::const_iterator end() const;

    void erase(std::vector<Country*>::const_iterator it);
private:
    QString _name;
    std::vector<Country*> _countries;
};

#endif // REGION_H
