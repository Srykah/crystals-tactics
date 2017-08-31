#include "Gameplay/Items/Inventory.hpp"

/// Loading

bool Inventory::loadFromNode(const pugi::xml_node& node)
{
    // write loading function here

    return true;
}

///Consumables

void Inventory::addConsumable(int id, short count)
{
    mConsumables.at(id) += count;
}

short Inventory::getConsumableCount(int id) const
{
    return mConsumables.at(id);
}

void Inventory::removeConsumable(int id, short count)
{
    if (mConsumables.at(id) >= count)
        mConsumables.at(id) -= count;
}

///Equipments

void Inventory::addEquipment(int id, short count)
{
    mEquipments.at(id).first += count;
}

short Inventory::getEquipmentCount(int id) const
{
    return mEquipments.at(id).first;
}

void Inventory::removeEquipment(int id, short count)
{
    if (mEquipments.at(id).first >= count)
        mEquipments.at(id).first -= count;
}

void Inventory::equipItem(int id)
{
    if (mEquipments.at(id).first > mEquipments.at(id).second)
        mEquipments.at(id).second++;
}

short Inventory::getEquippedCount(int id) const
{
    return mEquipments.at(id).second;
}

void Inventory::unequipItem(int id)
{
    if (mEquipments.at(id).second > 0)
        mEquipments.at(id).second--;
}

///Weapons

void Inventory::addWeapon(int id, short count)
{
    mWeapons.at(id).first += count;
}

short Inventory::getWeaponCount(int id) const
{
    return mWeapons.at(id).first;
}

void Inventory::removeWeapon(int id, short count)
{
    if (mWeapons.at(id).first >= count)
        mWeapons.at(id).first -= count;
}

void Inventory::equipWeapon(int id)
{
    if (mWeapons.at(id).first > mWeapons.at(id).second)
        mWeapons.at(id).second++;
}

short Inventory::getEquippedWeaponCount(int id) const
{
    return mWeapons.at(id).second;
}

void Inventory::unequipWeapon(int id)
{
    if (mWeapons.at(id).second > 0)
        mWeapons.at(id).second--;
}

///QuestItems

void Inventory::addQuestItem(int id)
{
    mQuestItems.at(id) = true;
}

short Inventory::hasQuestItem(int id) const
{
    return mQuestItems.at(id);
}

void Inventory::removeQuestItem(int id)
{
    mQuestItems.at(id) = false;
}

///Money

void Inventory::gainMoney(int amount)
{
    mMoney += amount;
}

void Inventory::loseMoney(int amount)
{
    if (mMoney >= amount)
        mMoney -= amount;
}

int Inventory::getMoney() const
{
    return mMoney;
}
