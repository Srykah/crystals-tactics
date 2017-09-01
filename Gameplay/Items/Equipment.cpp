#include "Gameplay/Items/Equipment.hpp"
#include <sstream>

Equipment::Equipment()
: mPosition(Nowhere)
{

}

Equipment::~Equipment()
{

}

void Equipment::load(const pugi::xml_node& node)
{
    EquipmentBase::load(node);
    mPosition = StrToEqpPos(node.attribute("position").as_string());
    mAffinities.load(node.child("affinities"));
}

Equipment::Position Equipment::getPosition() const
{
    return mPosition;
}

const ElemAffinities& Equipment::getAffinities() const
{
    return mAffinities;
}

Equipment::Position StrToEqpPos(const sf::String& text)
{
    if (text == "head") return Equipment::Head;
    else if (text == "body") return Equipment::Body;
    else if (text == "legs") return Equipment::Legs;
    else if (text == "accessory") return Equipment::Accessory;
    else return Equipment::Nowhere;
}
