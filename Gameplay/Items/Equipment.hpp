#ifndef EQUIPMENT_HPP_INCLUDED
#define EQUIPMENT_HPP_INCLUDED

#include "Gameplay/Items/EquipmentBase.hpp"
#include "Gameplay/General/Element.hpp"
#include <memory>

class Equipment : public EquipmentBase
{
public:
    enum Position
    {
        Nowhere = -1,
        Head = 0,
        Body,
        Legs,
        Accessory
    };

    typedef std::shared_ptr< Equipment > SPtr;

    Equipment();
    ~Equipment();

    void                    load(const pugi::xml_node& node);
    Position                getPosition() const;
    const ElemAffinities&   getAffinities() const;

private:
    Position mPosition;
    ElemAffinities mAffinities;
};

Equipment::Position StrToEqpPos(const sf::String& text);

#endif // EQUIPMENT_HPP_INCLUDED
