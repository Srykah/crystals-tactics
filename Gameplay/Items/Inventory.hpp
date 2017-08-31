#ifndef INVENTORY_HPP_INCLUDED
#define INVENTORY_HPP_INCLUDED

#include "XML/pugixml.hpp"
#include <vector>

class Inventory
{
public:
    bool loadFromNode(const pugi::xml_node& node);

    void addConsumable(int itemID, short count = 1);
    short getConsumableCount(int itemID) const;
    void removeConsumable(int itemID, short count = 1);

    void addEquipment(int itemID, short count = 1);
    short getEquipmentCount(int itemID) const;
    void removeEquipment(int itemID, short count = 1);

    void equipItem(int);
    short getEquippedCount(int) const;
    void unequipItem(int);

    void addWeapon(int itemID, short count = 1);
    short getWeaponCount(int itemID) const;
    void removeWeapon(int itemID, short count = 1);

    void equipWeapon(int);
    short getEquippedWeaponCount(int) const;
    void unequipWeapon(int);

    void addQuestItem(int itemID);
    short hasQuestItem(int itemID) const;
    void removeQuestItem(int itemID);

    void gainMoney(int amount);
    void loseMoney(int amount);
    int getMoney() const;

private:
    std::vector< int > mConsumables;
    std::vector< std::pair<int,int> > mEquipments;
    std::vector< std::pair<int,int> > mWeapons;
    std::vector< bool > mQuestItems;

    int mMoney;
};


#endif // INVENTORY_HPP_INCLUDED
