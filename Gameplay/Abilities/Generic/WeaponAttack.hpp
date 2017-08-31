#ifndef WEAPONATTACK_HPP_INCLUDED
#define WEAPONATTACK_HPP_INCLUDED

#include "Gameplay/Abilities/Ability.hpp"
#include "Graphism/Scene/Effect.hpp"
#include "Graphism/Entity/Entity.hpp"
#include "Graphism/Text.hpp"
#include "States/Arch/Context.hpp"

namespace Ab
{

class WeaponAttack : public Ability
{
public:
    WeaponAttack();
    ~WeaponAttack();

    virtual std::vector<sf::Vector2i>   getRange(Character* user) const;
    virtual std::vector<sf::Vector2i>   getArea(Character* user, sf::Vector2i to) const;
    virtual void                        use(Character* user, sf::Vector2i to) const;
};


}

#endif // WEAPONATTACK_HPP_INCLUDED
