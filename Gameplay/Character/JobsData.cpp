#include "Data/Gameplay/StatsData.hpp"
#include "Other/Utility.hpp"
#include "Gameplay/General/Routines.hpp"
#include <cmath>

namespace
{

Stat getGrowth(float val)
{
    return Stat(val) + (randomFloatNorm() < (val-std::floor(val)));
}

}

namespace dt
{

bool Statsdt::load(const pugi::xml_node& node)
{
    mBase.load(node.child("base"));
    for (pugi::xml_attribute attr : node.child("level_up").attributes())
        mGrowth[StrToStatName(attr.name())] = attr.as_float();
    return true;
}

Stats Statsdt::getBase() const
{
    return mBase;
}

Stats Statsdt::getLvUpStats() const
{
    Stats stats;
    stats.maxHP = getGrowth(mGrowth.at(Stats::MAX_HP));
    stats.speed = getGrowth(mGrowth.at(Stats::SPEED));
    stats.mobility = getGrowth(mGrowth.at(Stats::MOBILITY));
    stats.attack = getGrowth(mGrowth.at(Stats::ATTACK));
    stats.defense = getGrowth(mGrowth.at(Stats::DEFENSE));
    stats.evasion = getGrowth(mGrowth.at(Stats::EVASION));
    stats.critHitRate = getGrowth(mGrowth.at(Stats::CRITHITRATE));

    return stats;
}

}
