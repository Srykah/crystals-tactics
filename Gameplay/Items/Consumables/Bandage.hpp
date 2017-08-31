#ifndef CONSUMABLE_HPP_INCLUDED
#define CONSUMABLE_HPP_INCLUDED

#include "Gameplay/Abilities/Ability.hpp"

class Character;

class Bandage : public Ab::Ability
{
public:
            Bandage();
    virtual ~Bandage();

    virtual std::vector<sf::Vector2i>   getRange(Character* user) const;
    virtual std::vector<sf::Vector2i>   getArea(Character* user, sf::Vector2i to) const;
    virtual void                        use(Character* user, sf::Vector2i to) const;
};


#endif // CONSUMABLE_HPP_INCLUDED
