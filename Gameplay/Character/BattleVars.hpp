#ifndef BATTLEVARS_HPP_INCLUDED
#define BATTLEVARS_HPP_INCLUDED

#include <SFML/System/Vector2.hpp>
#include "Gameplay/General/Stats.hpp"
#include "Gameplay/General/Direction.hpp"
#include "Gameplay/General/StatusAilment.hpp"

namespace ch
{

struct BattleVars
{
    sf::Vector2i coords;
    Direction::Dir facing;
    bool hasMoved, hasActed;
    Stat speedCounter;
    Stat HP;
};

}

#endif // BATTLEVARS_HPP_INCLUDED
