#include "../Gameplay/Weapon.hpp"

Weapon::Weapon(Type type, Weapons::ID id,
               const sf::String& name, const sf::String& description,
               float damage, int range,
               Stats stats)
: mType(type)
, mID(id)
, mName(name)
, mDescription(description)
, mDamage(damage)
, mRange(range)
, mStats(stats)
{

}

Weapon::~Weapon()
{

}

Weapon::Type Weapon::getType() const
{
    return mType;
}

bool Weapon::isMelee() const
{
    return mType == Weapon::Sword || mType == Weapon::Dagger;
}

Weapons::ID Weapon::getID() const
{
    return mID;
}

const sf::String& Weapon::getName() const
{
    return mName;
}

const sf::String& Weapon::getDescription() const
{
    return mDescription;
}

float Weapon::getDamage() const
{
    return mDamage;
}

int Weapon::getRange() const
{
    return mRange;
}

Stats Weapon::getStats() const
{
    return mStats;
}
