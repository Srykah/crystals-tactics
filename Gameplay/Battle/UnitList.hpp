#ifndef UNITLIST_HPP_INCLUDED
#define UNITLIST_HPP_INCLUDED

#include "Gameplay/Character/Character.hpp"
#include <unordered_map>

class UnitList
{
public:
    typedef short Key;

private:
    struct Unit
    {
        Unit(Character* unit, short exp) : unit(unit), exp(exp) {}

        Character* unit;
        short exp;
    };

    typedef std::pair<Key, Unit> Pair;
    typedef std::unordered_map<Key, Unit> UnitMap;
    typedef UnitMap::const_iterator It;

public:
    UnitList();
    ~UnitList();

    Key addUnit(Character* unit);
    Character* getUnit(Key key) const;
    Character* getUnitByTile(sf::Vector2i tile);
    Key getUnitKeyByTile(sf::Vector2i tile) const;
    void giveUnitExp(Key key, short exp);
    short getUnitExp(Key key) const;
    int getUnitCount() const;
    void removeUnit(Key key);

    bool battleWon() const;
    bool battleLost() const;
    void grantExperience();

private:
    UnitMap mUnits;
    UnitMap mDeadUnits;
    Key mKey;
};


#endif // UNITLIST_HPP_INCLUDED
