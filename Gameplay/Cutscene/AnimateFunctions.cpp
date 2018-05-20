#include "Gameplay/Cutscene/AnimateFunctions.hpp"
#include "Gameplay/Abilities/AbilityFunctions.hpp"
#include "Gameplay/Character/Character.hpp"
#include "Gameplay/Battle/UnitList.hpp"
#include "Gameplay/Battle/Battlefield.hpp"
#include "Gameplay/Items/Weapon.hpp"
#include "Gameplay/Cutscene/Cutscene.hpp"
#include "Other/Utility.hpp"

namespace Animate
{

void attack(Character* charac, sf::Vector2i to)
{
    // get orientation
    Direction::Dir dir(Ab::dirTowards(charac->getCoords(), to));

    Weapon* wpn(charac->getBuild().weapon);
    sf::String animName("bareFistAttack");
    if (wpn)
    {
        switch(wpn->getType())
        {
        case Weapon::Type::Knife:
            animName = "knifeAttack";
            break;

        case Weapon::Type::Mace:
            animName = "maceAttack";
            break;

        case Weapon::Type::Pistol:
            animName = "pistolAttack";
            break;

        case Weapon::Type::Canon:
            animName = "canonAttack";
            break;
        }
    }

    charac->getBattleContext().cutscene->addEvent(CutsceneEvent(charac, animName, dir));
}

void takeDamage(Character* charac, int dmg)
{

}

void counterattack(Character* counterattacker, Character* victim)
{

}

}
