#ifndef CHARACTERSTRUCTS_HPP_INCLUDED
#define CHARACTERSTRUCTS_HPP_INCLUDED

#include <array>
#include <SFML/System/String.hpp>

class Weapon;
class Equipment;

enum class CharType
{
    Unknown         = -1,
    Protector       = 0,
    Medic           = 1,
    Sniper          = 2,
    Mechanics       = 3,
    Spy             = 4,
    Bomber          = 5,
    Physicist       = 6,
    Acrobat         = 7,
    Rider           = 8,
    /*
    Wolf            = 13,
    Robodog         = 14,
    Robospider      = 15,
    Robotortoise    = 16,
    Robobear        = 17,
    Robotiger       = 18,
    MadAndroid      = 20
    */
    Count
};

enum class CharRole
{
    Hero,
    Boss,
    Target,
    Guest,
    Escort,
    None
};

struct CharBuild
{
    CharBuild() : weapon(nullptr), head(nullptr), body(nullptr), legs(nullptr), accessory(nullptr) {}

    Weapon* weapon;
    Equipment *head, *body, *legs, *accessory;
};

struct CharAbility
{
    CharAbility(int id = -1, int counter = 0) : id(id), counter(counter) {}

    int id, counter;
};

const size_t NB_ABILITIES(4);
typedef std::array<CharAbility, NB_ABILITIES> AbilityArray;

sf::String          CharTypeToStr(CharType type);
CharType            StrToCharType(const sf::String& text);
sf::String          CharRoleToStr(CharRole role);
CharRole            StrToCharRole(const sf::String& text);

#endif // CHARACTERENUMS_HPP_INCLUDED
