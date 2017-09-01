#ifndef STATS_HPP_INCLUDED
#define STATS_HPP_INCLUDED

#include "XML/pugixml.hpp"
#include <SFML/System/String.hpp>

typedef short Stat;

struct Stats
{
    enum Name
    {
        MAX_HP,
        SPEED,
        MOBILITY,
        ATTACK,
        DEFENSE,
        EVASION,
        CRITHITRATE
    };

    Stats();
    Stats(Stat _maxHP,
          Stat _speed,
          Stat _mobility,
          Stat _attack,
          Stat _defense,
          Stat _evasion,
          Stat _critHitRate);

    Stat maxHP;
    Stat speed;
    Stat mobility;
    Stat attack;
    Stat defense;
    Stat evasion;
    Stat critHitRate;

    void load(const pugi::xml_node& node);

    Stats& operator+=(Stats const& other);
};

Stats operator+(Stats const& first, Stats const& second);

sf::String          StatNameToStr(Stats::Name statName);
Stats::Name         StrToStatName(const sf::String& text);

#endif // STATS_HPP_INCLUDED
