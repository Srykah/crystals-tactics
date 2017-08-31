#include "Gameplay/Items/Consumables/Bandage.hpp"
#include "Gameplay/Character/Character.hpp"
#include "Gameplay/Abilities/AbilityFunctions.hpp"

Bandage::Bandage()
: Ability("Bandage", "Soigne une unité organique.", 0)
{

}

Bandage::~Bandage()
{

}

std::vector<sf::Vector2i> Bandage::getRange(Character* user) const
{
    return Ab::circleRange(user, 0, 1);
}

std::vector<sf::Vector2i> Bandage::getArea(Character* user, sf::Vector2i to) const
{
    return std::vector<sf::Vector2i>(1, to);
}

void Bandage::use(Character* user, sf::Vector2i to) const
{
    // function to write
}
