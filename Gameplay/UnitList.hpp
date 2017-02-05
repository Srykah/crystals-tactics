#ifndef UNITLIST_HPP_INCLUDED
#define UNITLIST_HPP_INCLUDED

#include "../Gameplay/Character.hpp"
#include <vector>

class UnitList
{
public:
    typedef short Key;
    typedef std::pair<Key, Character*> Pair;
    typedef std::vector<Pair>::const_iterator It;

public:
    UnitList();
    ~UnitList();

    void update(sf::Time delta);

    Key addUnit(Character* unit);
    void removeUnit(Key key);
    Character* getUnit(Key key) const;
    int getUnitCount() const;
    Character* getUnitByTile(sf::Vector2i tile);
    Key getUnitKeyByTile(sf::Vector2i tile) const;

    void sortUnits();

    It begin() const;
    It end() const;

private:
    std::vector<Pair> mUnits;
    Key mKey;
};


#endif // UNITLIST_HPP_INCLUDED
