#ifndef BUILD_HPP_INCLUDED
#define BUILD_HPP_INCLUDED

#include "Gameplay/General/Element.hpp"
#include "Gameplay/General/Stats.hpp"

class Weapon;
class Equipment;

namespace ch
{

struct Build
{
    Build();

    Stats           getStats() const;
    ElemAffinities  getAffinities() const;
    void            equip(Equipment* eqp);
    void            equipWeapon(Weapon* eqp);

    Weapon* weapon;
    Equipment *head, *body, *legs, *accessory;
};

}

#endif // BUILD_HPP_INCLUDED
