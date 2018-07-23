#ifndef UNITLIST_HPP_INCLUDED
#define UNITLIST_HPP_INCLUDED

#include "Gameplay/Character/Character.hpp"
#include <SFML/System/Time.hpp>
#include <vector>

namespace bt
{

class UnitList
{
public:
    UnitList();
    ~UnitList();

    void update(sf::Time dt);

    void addUnit(Character* unit);
    void removeUnit(Character* charac);

    Character* getUnitByTile(sf::Vector2i tile);
    int getLivingUnitCount() const;
    int getDeadUnitCount()   const;
    int getTotalUnitCount()  const;

    void incrementCounters();
    Character* getReadyUnit() const;
    void checkForDeadUnits();

    bool battleWon() const;
    bool battleLost() const;

private:
    std::vector<Character*> mUnits;
    std::vector<Character*> mDeadUnits;
};

}

#endif // UNITLIST_HPP_INCLUDED
