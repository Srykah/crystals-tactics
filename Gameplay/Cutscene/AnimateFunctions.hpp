#ifndef ANIMATEFUNCTIONS_HPP_INCLUDED
#define ANIMATEFUNCTIONS_HPP_INCLUDED

#include <SFML/System/Vector2.hpp>

class Character;

namespace Animate
{
    void attack(Character* charac, sf::Vector2i to);
    void takeDamage(Character* charac, int dmg);
    void counterattack(Character* counterattacker, Character* victim);
}

#endif // ANIMATEFUNCTIONS_HPP_INCLUDED
