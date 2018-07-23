#ifndef MOVEMENT_HPP_INCLUDED
#define MOVEMENT_HPP_INCLUDED

#include "Gameplay/Abilities/Ability.hpp"
#include "Data/DataIdentifiers.hpp"
#include "Gameplay/General/Direction.hpp"
#include "Graphism/Scene/Effect.hpp"
#include "States/Arch/Context.hpp"
#include <deque>
#include <map>

class BattleField;
class UnitList;

namespace ab
{

class Movement : public Ability
{
public:
                                        Movement();
                                        ~Movement();

    virtual std::vector<sf::Vector2i>   getRange(Character* user) const;
    virtual std::vector<sf::Vector2i>   getArea(Character* user, sf::Vector2i to) const;
    virtual void                        use(Character* user, sf::Vector2i to) const;
};

}

#endif // MOVEMENT_HPP_INCLUDED
