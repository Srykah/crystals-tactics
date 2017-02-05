#ifndef STATS_HPP_INCLUDED
#define STATS_HPP_INCLUDED

#include "../Other/pugixml.hpp"

typedef short Stat;

struct Stats
{
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

#endif // STATS_HPP_INCLUDED
