#ifndef ABILITYFUNCTIONS_HPP_INCLUDED
#define ABILITYFUNCTIONS_HPP_INCLUDED

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <utility>
#include "Gameplay/General/Direction.hpp"
#include "Gameplay/General/Stats.hpp"
#include "Gameplay/General/Element.hpp"
#include "Gameplay/General/StatusAilment.hpp"

class Character;
class Battlefield;
class UnitList;

/*
namespace ab
{
    namespace Range
    { enum Type
        {
            Self = 0,
            Circle,
            Square,
            Cross,
            Weapon,
            All
        };
    }

    namespace Area
    {
        enum AreaType
        {
            Unit = 0,
            Circle,
            Square,
            Cross,
            Line,
            LinePerp,
            All
        };
    }
}*/

namespace ab
{
    bool                        isVisible(const Character* user, sf::Vector2i cible); // to rewrite

    std::vector<sf::Vector2i>   circleRange(const Character* user, int min, int max);
    std::vector<sf::Vector2i>   squareRange(const Character* user, int min, int max);
    std::vector<sf::Vector2i>   crossRange(const Character* user, int min, int max);

    std::vector<sf::Vector2i>   circleArea(sf::Vector2i tile, int min, int max, const Battlefield* bf);
    std::vector<sf::Vector2i>   squareArea(sf::Vector2i tile, int min, int max, const Battlefield* bf);
    std::vector<sf::Vector2i>   crossArea(sf::Vector2i tile, int min, int max, const Battlefield* bf);
    std::vector<sf::Vector2i>   lineArea(sf::Vector2i tile, int min, int max, const Character* user);
    std::vector<sf::Vector2i>   linePerpArea(sf::Vector2i tile, int min, int max, const Character* user);

    Direction::Dir              dirTowards(sf::Vector2i from, sf::Vector2i to);
    Direction::Angle            getAngle(sf::Vector2i from, Character* target);

    bool                        escapes(const Character* charac, Direction::Angle angle);
    bool                        counterattacks(const Character* charac, Direction::Angle angle);

    void                        dealDamage(Stat baseDmg, Character* attacker, Character* target, Element elem = Element::None, SA ailment = SA());
    void                        pushFrom(Character* charac, sf::Vector2i from, int tile_count = 1); // to do
}

#endif // ABILITYFUNCTIONS_HPP_INCLUDED
