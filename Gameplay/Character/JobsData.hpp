#ifndef STATSDATA_HPP_INCLUDED
#define STATSDATA_HPP_INCLUDED

#include "Gameplay/General/Stats.hpp"
#include "XML/pugixml.hpp"
#include <map>

namespace dt
{

class StatsData
{
public:
    bool load(const pugi::xml_node& node);

    Stats getBase() const;
    Stats getLvUpStats() const;

private:
    Stats mBase;
    std::map< Stats::Name, float > mGrowth;
};

}

#endif // STATSDATA_HPP_INCLUDED
