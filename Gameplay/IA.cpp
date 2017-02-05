#include "../Gameplay/IA.hpp"
#include "../Gameplay/Character.hpp"

const sf::Time thinkingTime = sf::seconds(1.5);

IA::IA(Character* charac, Type type)
: mCharac(charac)
, mType(type)
{

}

IA::~IA()
{

}

void IA::setType(Type type)
{
    mType = type;
}

IA::Type IA::getType() const
{
    return mType;
}

void IA::newTurn()
{
    mTime = sf::Time::Zero;
}

void IA::update(sf::Time delta)
{
    mTime += delta;
    if (mTime > thinkingTime)
        mCharac->endTurn();
}

IA::Type convertStringToIA(std::string str)
{
    if (str == "balanced")
        return IA::Balanced;
    else if (str == "aggressive")
        return IA::Aggressive;
    else if (str == "defensive")
        return IA::Defensive;
    else return IA::None;
}

