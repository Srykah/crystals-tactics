#include "Gameplay/Items/EquipmentBase.hpp"
#include "Other/Utility.hpp"
#include <SFML/System/String.hpp>

EquipmentBase::EquipmentBase()
: mID(-1)
{

}

EquipmentBase::~EquipmentBase()
{

}

void EquipmentBase::load(const pugi::xml_node& node)
{
    mID = node.attribute("id").as_int();
    mName = sf::String(node.attribute("name").as_string());
    mDescription = sf::String(node.child("description").text().get());
    mStats.load(node.child("stats"));
    if (!node.child("types") || sf::String(node.child("types").text().as_string()) == sf::String("All"))
    {
        for (int i : getRange<CharType>())
            mUsedBy.push_back(CharType(i));
    }
    else
    {
        std::stringstream ss(node.child("types").text().as_string());
        std::string typeName;
        while (std::getline(ss, typeName, ','))
            mUsedBy.push_back(StrToCharType(typeName));
    }
}

int EquipmentBase::getID() const
{
    return mID;
}

const sf::String& EquipmentBase::getName() const
{
    return mName;
}

const sf::String& EquipmentBase::getDescription() const
{
    return mDescription;
}

Stats EquipmentBase::getStats() const
{
    return mStats;
}

bool EquipmentBase::canBeEquipped(CharType type) const
{
    return std::find(mUsedBy.begin(), mUsedBy.end(), type) != mUsedBy.end();
}
