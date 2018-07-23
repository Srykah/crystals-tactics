#ifndef DATAIDENTIFIERS_HPP_INCLUDED
#define DATAIDENTIFIERS_HPP_INCLUDED

#include "Data/ResourceHolder.hpp"
#include "Data/DataHolder.hpp"
#include <map>
#include <memory>

namespace sf
{
    class Texture;
    class Font;
}

namespace ch { class JobsData; }

namespace ab { class Ability; }

namespace it
{
    class Equipment;
    class Weapon;
}

namespace en { class EntityData; }

namespace dt
{
    typedef ResourceHolder<sf::Texture> TextureHolder;
    typedef ResourceHolder<sf::Font>    FontHolder;
    typedef DataHolder<it::Equipment>   EquipmentHolder;
    typedef DataHolder<it::Weapon>      WeaponHolder;
    typedef DataHolder<ch::JobsData>    StatsHolder;
    typedef DataHolder<en::EntityData>  EntityHolder;
    typedef std::map< std::string, std::unique_ptr<ab::Ability> >   AbilityHolder;
}

#endif // DATAIDENTIFIERS_HPP_INCLUDED
