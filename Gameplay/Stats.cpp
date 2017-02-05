#include "../Gameplay/Stats.hpp"

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
