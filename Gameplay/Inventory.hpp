#ifndef INVENTORY_HPP_INCLUDED
#define INVENTORY_HPP_INCLUDED

#include "../Gameplay/Consumable.hpp"
#include "../Gameplay/Equipment.hpp"
#include "../Gameplay/Weapon.hpp"
#include "../Gameplay/QuestItem.hpp"
#include <map>

class Inventory
{
public:
    void addConsumable(Consumables::ID itemID, short count = 1);
    short getConsumableCount(Consumables::ID itemID) const;
    void removeConsumable(Consumables::ID itemID, short count = 1);

    void addEquipment(Equipments::ID itemID, short count = 1);
    short getEquipmentCount(Equipments::ID itemID) const;
    void removeEquipment(Equipments::ID itemID, short count = 1);

    void equipItem(Equipments::ID);
    short getEquippedCount(Equipments::ID) const;
    void unequipItem(Equipments::ID);

    void addWeapon(Weapons::ID itemID, short count = 1);
    short getWeaponCount(Weapons::ID itemID) const;
    void removeWeapon(Weapons::ID itemID, short count = 1);

    void equipWeapon(Weapons::ID);
    short getEquippedWeaponCount(Weapons::ID) const;
    void unequipWeapon(Weapons::ID);

    void addQuestItem(QuestItems::ID itemID);
    short hasQuestItem(QuestItems::ID itemID) const;
    void removeQuestItem(QuestItems::ID itemID);

    void gainMoney(int amount);
    void loseMoney(int amount);
    int getMoney() const;

private:
    std::map< Consumables::ID, int > mConsumables;
    std::map< Equipments::ID, std::pair<int,int> > mEquipments;
    std::map< Weapons::ID, std::pair<int,int> > mWeapons;
    std::map< QuestItems::ID, bool > mQuestItems;

    int mMoney;
};


#endif // INVENTORY_HPP_INCLUDED
