#ifndef ABILITYDATA_HPP_INCLUDED
#define ABILITYDATA_HPP_INCLUDED

#include <SFML/System/String.hpp>
#include <vector>
#include "../Other/pugixml.hpp"

namespace Ab
{

    struct Range
    {
        enum Type
        {
            Self = 0,
            Circle,
            Square,
            Cross,
            Weapon,
            All
        };
        /*static const int Self;
        static const int Circle;
        static const int Square;
        static const int Cross;
        static const int Weapon;
        static const int All;*/

        int type;
        int minRange, maxRange;
    };

    struct Area
    {
        enum Type
        {
            Unit = 0,
            Circle,
            Square,
            Cross,
            Line,
            LinePerp,
            All
        };
        /*static const int Unit;
        static const int Circle;
        static const int Square;
        static const int Cross;
        static const int Line;
        static const int LinePerp;
        static const int All;*/

        Type type;
        int minArea, maxArea;
    };

    /*namespace AbilityEffect
    {
        static const Damage(0);
        static const Heal(1);
        static const Status(2);
    }*/

    enum Effect
    {
        Damage = 0,
        Heal,
        Status
    };

}

namespace Data
{

    struct AbilityData
    {
        sf::String name, description;
        Ab::Range abRange;
        Ab::Area abArea;
        short cooldown;
        short power;
        short accuracy;
    };

    typedef std::vector<AbilityData> AbsData;

    AbsData loadAbilities(const std::string& filename);

}

#endif // ABILITYDATA_HPP_INCLUDED
