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

    enum class Type
    {
        None = -1,
        Knife = 0,
        Mace,
        Pistol,
        Canon,
        Count
    };

    Weapon();
    ~Weapon();

    void                load(const pugi::xml_node& node);
    int                 getDamage() const;
    int                 getRangeMin() const;
    int                 getRangeMax() const;
    int                 getPrecision() const;
    Element             getElement() const;
    StatusAilment       getAilment() const;

private:
    Type mType;
    int mDamage;
    int mRangeMin, mRangeMax;
    int mPrecision;
    Element mElement;
    StatusAilment mAilment;
};

Weapon::Type StrToWpnType(const sf::String& str);

#endif // WEAPON_HPP_INCLUDED
