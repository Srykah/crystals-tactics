#include "../Gameplay/UnitList.hpp"
#include <cassert>

UnitList::UnitList()
{

}

UnitList::~UnitList()
{

}

void UnitList::update(sf::Time delta)
{
    for(auto unit : mUnits)
        unit.second->update(delta);
}

UnitList::Key UnitList::addUnit(Character* unit)
{
    assert(unit != nullptr);
    auto it = std::find_if(mUnits.begin(), mUnits.end(), [unit](Pair obj){ return obj.second == unit; });
    mUnits.insert(it, std::make_pair(mKey, unit));
    return mKey++;
}

void UnitList::removeUnit(UnitList::Key key)
{
    auto it = std::find_if(mUnits.begin(), mUnits.end(), [key](Pair obj){ return obj.first == key; });
    if (it != mUnits.end())
        mUnits.erase(it);
}

Character* UnitList::getUnit(UnitList::Key key) const
{
    auto it = std::find_if(mUnits.begin(), mUnits.end(), [key](Pair obj){ return obj.first == key; });
    if (it != mUnits.end())
        return it->second;
    else
        return nullptr;
}

int UnitList::getUnitCount() const
{
    return mUnits.size();
}

Character* UnitList::getUnitByTile(sf::Vector2i tile)
{
    auto it = std::find_if(mUnits.begin(), mUnits.end(), [tile](Pair obj){ return obj.second->getCoords() == tile; });
    if (it != mUnits.end())
        return it->second;
    else
        return nullptr;
}

UnitList::Key UnitList::getUnitKeyByTile(sf::Vector2i tile) const
{
    auto it = std::find_if(mUnits.begin(), mUnits.end(), [tile](Pair obj){ return obj.second->getCoords() == tile; });
    if (it != mUnits.end())
        return it->first;
    else
        return -1;
}

void UnitList::sortUnits()
{
    std::sort(mUnits.begin(), mUnits.end(),
              [](Pair left, Pair right){ return left.second->getCoords().y >= left.second->getCoords().y; });
}

UnitList::It UnitList::begin() const
{
    return mUnits.begin();
}

UnitList::It UnitList::end() const
{
    return mUnits.end();
}
