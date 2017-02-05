#include "../Gameplay/Ability.hpp"
#include "../Gameplay/AbilityFunctions.hpp"
#include "../Gameplay/Character.hpp"
#include "../Gameplay/Weapon.hpp"
#include "../Gameplay/Battlefield.hpp"

Ability::Ability(Character* user, const Data::AbilityData& data)
: mData(data)
, mUser(user)
, mCounter(0)
{

}

Ability::~Ability()
{

}

const sf::String& Ability::getName() const
{
    return mData.name;
}

const sf::String& Ability::getDescription() const
{
    return mData.description;
}

std::vector<sf::Vector2i> Ability::getRange() const
{
    switch (mData.abRange.type)
    {
    case Ab::Range::Self:
        return std::vector<sf::Vector2i>(1, mUser->getCoords());

    case Ab::Range::Circle:
        return Ab::getCircleRange(mUser, mData.abRange.minRange, mData.abRange.maxRange);

    case Ab::Range::Square:
        return Ab::getSquareRange(mUser, mData.abRange.minRange, mData.abRange.maxRange);

    case Ab::Range::Cross:
        return Ab::getCrossRange(mUser, mData.abRange.minRange, mData.abRange.maxRange);

    case Ab::Range::Weapon:
        if (mUser->getBuild().weapon != nullptr)
            return Ab::getCircleRange(mUser, 1, mUser->getBuild().weapon->getRange());
        else
            return Ab::getCircleRange(mUser, 1, 1);

    case Ab::Range::All:
        std::vector<sf::Vector2i> tab;
        sf::Vector2i gridSize(mUser->getBattlefield()->getGridSize());
        for (int i(0); i < gridSize.x; i++)
        {
            for (int j(0); j < gridSize.y; j++)
            {
                sf::Vector2i tile(i,j);
                if (Ab::isVisible(mUser, tile))
                   tab.push_back(tile);
            }
        }
        return tab;
    }

    return std::vector<sf::Vector2i>();
}

std::vector<sf::Vector2i> Ability::getArea(sf::Vector2i to) const
{
    const Battlefield* bf(mUser->getBattlefield());
    int min(mData.abArea.minArea), max(mData.abArea.minArea);

    switch (mData.abArea.type)
    {
    case Ab::Area::Unit:
        return std::vector<sf::Vector2i>(1, to);
        break;

    case Ab::Area::Circle:
        return Ab::getCircleArea(to, min, max, bf);
        break;

    case Ab::Area::Square:
        return Ab::getSquareArea(to, min, max, bf);
        break;

    case Ab::Area::Cross:
        return Ab::getCrossArea(to, min, max, bf);
        break;

    case Ab::Area::Line:
        return Ab::getLineArea(to, min, max, bf);
        break;

    case Ab::Area::LinePerp:
        return Ab::getLinePerpArea(to, min, max, bf);
        break;

    case Ab::Area::All:
        std::vector<sf::Vector2i> tab;
        sf::Vector2i gridSize(bf->getGridSize());
        for (int i(0); i < gridSize.x; i++)
        {
            for (int j(0); j < gridSize.y; j++)
            {
                sf::Vector2i tile(i,j);
                if (!bf->isWall(tile)) // no need to check bounds here
                   tab.push_back(tile);
            }
        }
        return tab;
    }

    return std::vector<sf::Vector2i>();
}

short Ability::getCounter() const
{
    return mCounter;
}

void Ability::incrementCounter()
{
    if (mCounter < mData.cooldown)
        mCounter++;
}

bool Ability::isAvailable() const
{
    return mCounter >= mData.cooldown;
}

void Ability::use(sf::Vector2i to)
{
    mTile = to;
    mCounter = 0;
    // mState = ...
}

bool Ability::inProgress() const
{
    // return mState ...
    return false;
}

void Ability::update(sf::Time delta)
{

}
