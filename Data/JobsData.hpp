#ifndef JOBSDATA_HPP_INCLUDED
#define JOBSDATA_HPP_INCLUDED

#include <vector>
#include <string>

#include "../Gameplay/Stats.hpp"

namespace Data
{

typedef std::vector<Stats> StatsTab; /* int used in place of Character::Type */
struct StatsData
{
    StatsTab base;
    StatsTab levelUp;
};
const StatsData loadStats(const std::string& filename);

}

#endif // JOBSDATA_HPP_INCLUDED
