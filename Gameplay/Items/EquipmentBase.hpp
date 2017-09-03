#ifndef EQUIPMENTBASE_HPP_INCLUDED
#define EQUIPMENTBASE_HPP_INCLUDED

#include "Gameplay/General/Element.hpp"
#include "Gameplay/General/Stats.hpp"
#include "Gameplay/Character/CharacterStructs.hpp"
#include "XML/pugixml.hpp"
#include <SFML/System/String.hpp>

class EquipmentBase
{
public:
    EquipmentBase();
    ~EquipmentBase();

    void                    load(const pugi::xml_node& node);

    int                     getID() const;
    const sf::String&       getName() const;
    const sf::String&       getDescription() const;
    Stats                   getStats() const;
    //bool                    canBeEquipped(CharType type) const;

private:
    short mID;
    sf::String mName;
    sf::String mDescription;
    Stats mStats;
    //std::vector<CharType> mUsedBy;
};

#endif // EQUIPMENTBASE_HPP_INCLUDED
