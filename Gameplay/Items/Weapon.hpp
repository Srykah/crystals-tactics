#ifndef WEAPON_HPP_INCLUDED
#define WEAPON_HPP_INCLUDED

#include "Gameplay/Items/EquipmentBase.hpp"
#include "Gameplay/General/Element.hpp"
#include "Gameplay/General/StatusAilment.hpp"
#include <memory>

class Weapon : public EquipmentBase
{
public:
    typedef std::shared_ptr< Weapon > SPtr;

    Weapon();
    ~Weapon();

    void load(const pugi::xml_node& node);
    int                 getDamage() const;
    int                 getRange() const;
    Element             getElement() const;
    StatusAilment       getAilment() const; //not supported yet

private:
    int mDamage;
    int mRange;
    Element mElement;
    StatusAilment mAilment;
};


#endif // WEAPON_HPP_INCLUDED
