#include "../Gameplay/Inventory.hpp"

///Consumables

void Inventory::addConsumable(Consumables::ID id, short count)
{
    mConsumables.at(id) += count;
}

short Inventory::getConsumableCount(Consumables::ID id) const
{
    return mConsumables.at(id);
}

void Inventory::removeConsumable(Consumables::ID id, short count)
{
    if (mConsumables.at(id) >= count)
        mConsumables.at(id) -= count;
}

///Equipments

void Inventory::addEquipment(Equipments::ID id, short count)
{
    mEquipments.at(id).first += count;
}

short Inventory::getEquipmentCount(Equipments::ID id) const
{
    return mEquipments.at(id).first;
}

void Inventory::removeEquipment(Equipments::ID id, short count)
{
    if (mEquipments.at(id).first >= count)
        mEquipments.at(id).first -= count;
}

void Inventory::equipItem(Equipments::ID id)
{
    if (mEquipments.at(id).first > mEquipments.at(id).second)
        mEquipments.at(id).second++;
}

short Inventory::getEquippedCount(Equipments::ID id) const
{
    return mEquipments.at(id).second;
}

void Inventory::unequipItem(Equipments::ID id)
{
    if (mEquipments.at(id).second > 0)
        mEquipments.at(id).second--;
}

///Weapons

void Inventory::addWeapon(Weapons::ID id, short count)
{
    mWeapons.at(id).first += count;
}

short Inventory::getWeaponCount(Weapons::ID id) const
{
    return mWeapons.at(id).first;
}

void Inventory::removeWeapon(Weapons::ID id, short count)
{
    if (mWeapons.at(id).first >= count)
        mWeapons.at(id).first -= count;
}

void Inventory::equipWeapon(Weapons::ID id)
{
    if (mWeapons.at(id).first > mWeapons.at(id).second)
        mWeapons.at(id).second++;
}

short Inventory::getEquippedWeaponCount(Weapons::ID id) const
{
    return mWeapons.at(id).second;
}

void Inventory::unequipWeapon(Weapons::ID id)
{
    if (mWeapons.at(id).second > 0)
        mWeapons.at(id).second--;
}

///QuestItems

void Inventory::addQuestItem(QuestItems::ID id)
{
    mQuestItems.at(id) = true;
}

short Inventory::hasQuestItem(QuestItems::ID id) const
{
    return mQuestItems.at(id);
}

void Inventory::removeQuestItem(QuestItems::ID id)
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
