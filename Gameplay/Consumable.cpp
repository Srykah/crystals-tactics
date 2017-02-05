#include "../Gameplay/Consumable.hpp"

Consumable::Consumable(Consumables::ID id)
: mID(id)
{

}

Consumable::~Consumable()
{

}

/*
sf::String Consumable::getName() const
{
    return mEffect->getName();
}

sf::String Consumable::getDescription() const
{
    return mEffect->getDescription();
}
*/

Consumables::ID Consumable::getID() const
{
    return mID;
}

/*
std::vector<sf::Vector2i> Consumable::getRange(Character* user) const
{
    mEffect->setUser(user);
    return mEffect->getRange();
}

std::vector<sf::Vector2i> Consumable::getArea(Character* user, sf::Vector2i to) const
{
    mEffect->setUser(user);
    return mEffect->getArea(to);
}

void Consumable::use(Character* user, sf::Vector2i to)
{
    mEffect->setUser(user);
    return mEffect->use(to);
}

void Consumable::update(sf::Time delta)
{
    mEffect->update(delta);
}

bool Consumable::isBeingUsed() const
{
    return mEffect->inProgress();
}

*/
