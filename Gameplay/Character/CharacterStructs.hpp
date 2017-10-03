#ifndef CHARACTERSTRUCTS_HPP_INCLUDED
#define CHARACTERSTRUCTS_HPP_INCLUDED

#include <array>
#include <SFML/System/String.hpp>

class Weapon;
class Equipment;

enum class CharType
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

enum class CharRole
{
    None = -1,
    Hero = 0,
    Boss,
    Target,
    Guest,
    Escort,
    Count
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
