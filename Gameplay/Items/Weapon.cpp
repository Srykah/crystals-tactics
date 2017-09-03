#include "Gameplay/Items/Weapon.hpp"
#include "Gameplay/General/Routines.hpp"
#include <string>
#include <stdexcept>

Weapon::Weapon()
{

}

Weapon::~Weapon()
{

}

void Weapon::load(const pugi::xml_node& node)
{
    EquipmentBase::load(node);
    mType = StrToWpnType(node.attribute("type").as_string());
    mDamage = node.attribute("damage").as_int();
    mRangeMin = node.attribute("rangeMin").as_int();
    mRangeMax = node.attribute("rangeMax").as_int();
    mPrecision = node.attribute("precision").as_int();
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

Weapon::Type StrToWpnType(const sf::String& str)
{
         if (str == "knife")    return Weapon::Knife;
    else if (str == "mass")     return Weapon::Mace;
    else if (str == "pistol")   return Weapon::Pistol;
    else if (str == "canon")    return Weapon::Canon;
    else throw std::domain_error(str.toAnsiString() + std::string(" is not a weapon type"));
}
