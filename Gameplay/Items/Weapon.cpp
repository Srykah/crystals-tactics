#include "Gameplay/Items/Weapon.hpp"
#include "Gameplay/General/Routines.hpp"

Weapon::Weapon()
{

}

Weapon::~Weapon()
{

}

void Weapon::load(const pugi::xml_node& node)
{
    EquipmentBase::load(node);
    mDamage = node.attribute("damage").as_int();
    mRange = node.attribute("range").as_int();
    mElement = StrToElement(node.attribute("element").as_string());
    mAilment = StrToSA(node.attribute("ailment").as_string());
}

int Weapon::getDamage() const
{
    return mDamage;
}

int Weapon::getRange() const
{
    return mRange;
}

Element Weapon::getElement() const
{
    return mElement;
}

StatusAilment Weapon::getAilment() const
{
    return mAilment;
}
