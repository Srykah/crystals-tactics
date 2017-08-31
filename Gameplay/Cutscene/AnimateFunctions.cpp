#include "Gameplay/Cutscene/AnimateFunctions.hpp"
#include "Gameplay/Abilities/AbilityFunctions.hpp"
#include "Gameplay/Character/Character.hpp"
#include "Gameplay/Battle/UnitList.hpp"
#include "Gameplay/Battle/Battlefield.hpp"
#include "Gameplay/Items/Weapon.hpp"
#include "Gameplay/Cutscene/Cutscene.hpp"
#include "Other/Utility.hpp"
#include <iostream>

namespace Animate
{

void attack(Character* charac, sf::Vector2i to)
{
    // get orientation
    Direction::Dir dir(Ab::dirTowards(charac->getCoords(), to));

    charac->getBattleContext().cutscene->addEvent(CutsceneEvent(charac, "attack", dir));
}

void takeDamage(Character* charac, int dmg)
{

}

void counterattack(Character* counterattacker, Character* victim)
{

}

}
