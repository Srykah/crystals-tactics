#include "WeaponAttack.hpp"
#include "Gameplay/Character/Character.hpp"
#include "Gameplay/Items/Weapon.hpp"
#include "Gameplay/Battle/UnitList.hpp"
#include "Gameplay/Cutscene/AnimateFunctions.hpp"
#include "Other/Utility.hpp"

namespace Ab
{

WeaponAttack::WeaponAttack()
: Ability("Attaque", "Attaque standard. Peut être effectuée à chaque tour.", 1)
{

}

WeaponAttack::~WeaponAttack()
{

}

std::vector<sf::Vector2i> WeaponAttack::getRange(Character* user) const
{
    Weapon* wpn(user->getBuild().weapon);
    return circleRange(user, 1, (wpn ? wpn->getRange() : 1));
}

std::vector<sf::Vector2i> WeaponAttack::getArea(Character* user, sf::Vector2i to) const
{
    return std::vector<sf::Vector2i>(1, to);
}

void WeaponAttack::use(Character* user, sf::Vector2i to) const
{
    BattleContext bc(user->getBattleContext());

    Animate::attack(user, to); //animation attaque

    Character* target(bc.ul->getUnitByTile(to));
    if (target != nullptr) // si il y a quelqu'un à attaquer
    {
        int damage(10 + randomPick(user->getStats().attack) - 0.5*randomPick(target->getStats().defense));

        Animate::takeDamage(target, damage); //animation dégâts
        Animate::counterattack(target, user); //animation riposte
    }
}

}
