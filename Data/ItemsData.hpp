#ifndef CONSUMABLELIST_HPP_INCLUDED
#define CONSUMABLELIST_HPP_INCLUDED

#include <vector>
#include <string>

#include "../Other/pugixml.hpp"

class Equipment;
class Weapon;
class Consumable;

namespace Data
{

typedef std::vector<Equipment> EqpmtTab;
typedef std::vector<Weapon> WpnTab;
typedef std::vector<Consumable> ConsumTab;

struct ItemsData
{
    WpnTab weapons;
    EqpmtTab helms, armors, boots, accessories;
    ConsumTab consumables;
};

const ItemsData& loadItems(const std::string& filename);

}


#endif // CONSUMABLELIST_HPP_INCLUDED
