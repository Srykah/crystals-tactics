#include "Gameplay/General/Stats.hpp"
#include <stdexcept>

Stats::Stats()
: maxHP(0)
, speed(0)
, mobility(0)
, attack(0)
, defense(0)
, evasion(0)
, critHitRate(0)
{

}

Stats::Stats(Stat _maxHP, Stat _speed, Stat _mobility, Stat _attack, Stat _defense, Stat _evasion, Stat _critHitRate)
: maxHP(_maxHP)
, speed(_speed)
, mobility(_mobility)
, attack(_attack)
, defense(_defense)
, evasion(_evasion)
, critHitRate(_critHitRate)
{

}

void Stats::load(const pugi::xml_node& node)
{
    maxHP = node.attribute("maxHP").as_uint();
    speed = node.attribute("speed").as_uint();
    mobility = node.attribute("mobility").as_uint();
    attack = node.attribute("attack").as_uint();
    defense = node.attribute("defense").as_uint();
    evasion = node.attribute("evasion").as_uint();
    critHitRate = node.attribute("critHitRate").as_uint();
}

Stats& Stats::operator+=(Stats const& other)
{
    maxHP += other.maxHP;
    speed += other.speed;
    mobility += other.mobility;
    attack += other.attack;
    defense += other.defense;
    evasion += other.evasion;
    critHitRate += other.critHitRate;

    return *this;
}

Stats operator+(Stats const& first, Stats const& second)
{
    return Stats(first)+=second;
}

std::string StatNameToStr(Stats::Name statName)
{
    #define STATTOSTRING_CASE(STATNAME) case Stats::STATNAME: return #STATNAME;

    switch(statName)
    {
    case Stats::MAX_HP: return "maxHP";
    case Stats::SPEED: return "speed";
    case Stats::MOBILITY: return "mobility";
    case Stats::ATTACK: return "attack";
    case Stats::DEFENSE: return "defense";
    case Stats::EVASION: return "evasion";
    case Stats::CRITHITRATE: return "critHitRate";
    default:
        return "";
    }
}

Stats::Name StrToStatName(const std::string& text)
{
    #define STRINGTOSTAT_IF(TEXT, STATNAME) if (TEXT == #STATNAME) return Stats::STATNAME;

    if (text == "maxHP") return Stats::MAX_HP;
    else if (text == "mobility") return Stats::MOBILITY;
    else if (text == "speed") return Stats::SPEED;
    else if (text == "attack") return Stats::ATTACK;
    else if (text == "defense") return Stats::DEFENSE;
    else if (text == "evasion") return Stats::EVASION;
    else if (text == "critHitRate") return Stats::CRITHITRATE;
    else throw std::runtime_error(std::string("couldn't convert ") + text + std::string(" into stat name"));
}