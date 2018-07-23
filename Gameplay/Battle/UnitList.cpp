#include "Gameplay/Battle/UnitList.hpp"
#include <cassert>

namespace bt
{

UnitList::UnitList()
{

}

UnitList::~UnitList()
{

}

void UnitList::addUnit(Character* unit)
{
    assert(unit != nullptr);
    if(std::find(mUnits.begin(), mUnits.end(), unit) == mUnits.end())
        mUnits.push_back(unit);
}

void UnitList::removeUnit(Character* unit)
{
    mUnits.erase(std::remove(mUnits.begin(), mUnits.end(), unit));
    mDeadUnits.erase(std::remove(mUnits.begin(), mUnits.end(), unit));
}

Character* UnitList::getUnitByTile(sf::Vector2i tile)
{
    auto it = std::find_if(mUnits.begin(), mUnits.end(), [tile](Character* unit){ return unit->getCoords() == tile; });
    if (it != mUnits.end())
        return *it;
    else
        return nullptr;
}

int UnitList::getLivingUnitCount() const
{
    return mUnits.size();
}

int UnitList::getDeadUnitCount() const
{
    return mDeadUnits.size();
}

int UnitList::getTotalUnitCount() const
{
    return getLivingUnitCount() + getDeadUnitCount();
}

void UnitList::incrementCounters()
{
    for (Character* unit : mUnits)
        unit->incrementSpeedCounter();
}

Character* UnitList::getReadyUnit() const
{
    std::find_if(mUnits.begin(), mUnits.end(), )
}

}
