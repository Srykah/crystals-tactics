#ifndef ABILITYFUNCTIONS_HPP_INCLUDED
#define ABILITYFUNCTIONS_HPP_INCLUDED

#include <SFML/System/Vector2.hpp>
#include <vector>

class Character;
class Battlefield;

namespace Ab
{
    bool                        isVisible(const Character* user, sf::Vector2i tile); // to rewrite

    std::vector<sf::Vector2i>   getCircleRange(const Character* user, int min, int max);
    std::vector<sf::Vector2i>   getSquareRange(const Character* user, int min, int max);
    std::vector<sf::Vector2i>   getCrossRange(const Character* user, int min, int max);

    std::vector<sf::Vector2i>   getCircleArea(sf::Vector2i tile, int min, int max, const Battlefield* bf);
    std::vector<sf::Vector2i>   getSquareArea(sf::Vector2i tile, int min, int max, const Battlefield* bf);
    std::vector<sf::Vector2i>   getCrossArea(sf::Vector2i tile, int min, int max, const Battlefield* bf);
    std::vector<sf::Vector2i>   getLineArea(sf::Vector2i tile, int min, int max, const Battlefield* bf);
    std::vector<sf::Vector2i>   getLinePerpArea(sf::Vector2i tile, int min, int max, const Battlefield* bf);
}

#endif // ABILITYFUNCTIONS_HPP_INCLUDED
