#ifndef DATAIDENTIFIERS_HPP_INCLUDED
#define DATAIDENTIFIERS_HPP_INCLUDED

#include "Data/DataHolder/DataHolder.hpp"

class Equipment;
class Weapon;
class StatsData;

namespace Data
{
    typedef DataHolder<Equipment>   EquipmentHolder;
    typedef DataHolder<Weapon>      WeaponHolder;
    typedef DataHolder<StatsData>   StatsHolder;
}

#endif // DATAIDENTIFIERS_HPP_INCLUDED
