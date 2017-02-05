#include "../Gameplay/Equipment.hpp"

Equipment::Equipment(Position position, Type type, Equipments::ID id,
                     const sf::String& name, const sf::String& description,
                     Stats stats, Affinities affinities)
: mPosition(position)
, mType(type)
, mID(id)
, mName(name)
, mDescription(description)
, mStats(stats)
, mAffinities(affinities)
{

}

Equipment::~Equipment()
{

}

Equipment::Position Equipment::getPosition() const
{
    return mPosition;
}

Equipment::Type Equipment::getType() const
{
    return mType;
}

Equipments::ID Equipment::getID() const
{
    return mID;
}

const sf::String& Equipment::getName() const
{
    return mName;
}

const sf::String& Equipment::getDescription() const
{
    return mDescription;
}

Stats Equipment::getStats() const
{
    return mStats;
}

const Affinities& Equipment::getAffinities() const
{
    return mAffinities;
}
