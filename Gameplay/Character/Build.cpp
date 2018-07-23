#include "Gameplay/Character/Build.hpp"

namespace ch
{

Build::Build()
: weapon(nullptr)
, head(nullptr)
, body(nullptr)
, legs(nullptr)
, accessory(nullptr)
{

}

Stats Build::getStats() const
{
    Stats stats;

    if (weapon)
        stats += weapon->getStats();

    if (head)
        stats += head->getStats();

    if (body)
        stats += body->getStats();

    if (legs)
        stats += legs->getStats();

    if (accessory)
        stats += accessory->getStats();

    return stats;
}

ElemAffinities Build::getAffinities() const
{
    ElemAffinities aff;

    if (head)
        aff *= head->getAffinities();

    if (body)
        aff *= body->getAffinities();

    if (legs)
        aff *= legs->getAffinities();

    if (accessory)
        aff *= accessory->getAffinities();

    return aff;
}

void Character::equip(Equipment* eqp)
{
    switch (eqp->getPosition())
    {
    case Equipment::Head:
        mBuild.head = eqp;
        break;

    case Equipment::Body:
        mBuild.body = eqp;
        break;

    case Equipment::Legs:
        mBuild.legs = eqp;
        break;

    case Equipment::Accessory:
        mBuild.accessory = eqp;

    default:;
    }
}

void Character::equipWeapon(Weapon* weapon)
{
    mBuild.weapon = weapon;
}

}
