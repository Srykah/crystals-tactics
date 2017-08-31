#include "Gameplay/Abilities/Ability.hpp"
#include "Gameplay/Abilities/AbilityFunctions.hpp"
#include "Gameplay/Character/Character.hpp"
#include "Gameplay/Items/Weapon.hpp"
#include "Gameplay/Battle/Battlefield.hpp"

namespace Ab {

Ability::Ability(const sf::String& name, const sf::String& desc, short cooldown)
: mName(name)
, mDescription(desc)
, mCooldown(cooldown)
{

}

Ability::~Ability()
{

}

const sf::String& Ability::getName() const
{
    return mName;
}

const sf::String& Ability::getDescription() const
{
    return mDescription;
}

short Ability::getCooldown() const
{
    return mCooldown;
}

}
