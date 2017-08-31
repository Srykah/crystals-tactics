#include "Gameplay/Battle/UnitList.hpp"
#include <cassert>

UnitList::UnitList()
: mKey(0)
{

}

UnitList::~UnitList()
{

}

UnitList::Key UnitList::addUnit(Character* unit)
{
    assert(unit != nullptr);
    It iter(std::find_if(mUnits.begin(), mUnits.end(), [unit](Pair obj){ return obj.second.unit == unit; }));
    if(iter == mUnits.end())
    {
        mKey++;
        mUnits.insert({mKey, { unit, 0 }});
        return mKey;
    }
    else
        return iter->first;
}

Character* UnitList::getUnit(UnitList::Key key) const
{
    if (mUnits.count(key) > 0)
        return mUnits.at(key).unit;
    else
        return nullptr;
}

Character* UnitList::getUnitByTile(sf::Vector2i tile)
{
    auto it = std::find_if(mUnits.begin(), mUnits.end(), [tile](Pair obj){ return obj.second.unit->getCoords() == tile; });
    if (it != mUnits.end())
        return it->second.unit;
    else
        return nullptr;
}

UnitList::Key UnitList::getUnitKeyByTile(sf::Vector2i tile) const
{
    auto it = std::find_if(mUnits.begin(), mUnits.end(), [tile](Pair obj){ return obj.second.unit->getCoords() == tile; });
    if (it != mUnits.end())
        return it->first;
    else
        return -1;
}

void UnitList::giveUnitExp(Key key, short exp)
{
    if (mUnits.count(key) > 0)
        mUnits.at(key).exp += exp;
}

short UnitList::getUnitExp(Key key) const
{
    if (mUnits.count(key) > 0)
        return mUnits.at(key).exp;
    else
        return 0;
}

int UnitList::getUnitCount() const
{
    return mUnits.size();
}

void UnitList::removeUnit(UnitList::Key key)
{
    auto it = mUnits.find(key);
    if (it != mUnits.end())
        mUnits.erase(it);
}
