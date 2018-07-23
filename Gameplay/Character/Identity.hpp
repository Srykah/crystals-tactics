#ifndef IDENTITY_HPP_INCLUDED
#define IDENTITY_HPP_INCLUDED

#include <SFML/System/String.hpp>
#include "Gameplay/General/Stats.hpp"
#include "Gameplay/Character/AI.hpp"

namespace ch
{

struct Identity
{
    enum Sex
    {
        Male,
        Female,
        None
    };

    enum Race
    {
        Bio,
        Mech,
        Hybrid,
        Other
    };

    enum Job
    {
        Unknown = -1,
        Protector = 0,
        Medic,
        Sniper,
        Mechanics,
        Spy,
        Bomber,
        Physicist,
        Acrobat,
        Count
    };

    enum class Role
    {
        None = -1,
        Hero = 0,
        Boss,
        Target,
        Guest,
        Escort
    };

    Stat ID;
    sf::String name;
    Sex sex;
    Race race;
    Job job;
    Role role;
    bool alignment;
    Stat level;
    Stat exp;
    AI::Type ai;

    void load(pugi::xml_node node);
};

}

#endif // IDENTITY_HPP_INCLUDED
