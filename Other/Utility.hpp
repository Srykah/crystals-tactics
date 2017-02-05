#ifndef BOOK_UTILITY_HPP
#define BOOK_UTILITY_HPP

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

#include <sstream>


namespace sf
{
	class Sprite;
}

namespace Graphism
{
    class Animation;
    class Text;
}

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
std::string		toString(const T& value);

// Convert enumerators to strings
std::string		toString(sf::Keyboard::Key key);

// Call setOrigin() with the center of the object
template <typename T>
void			centerOrigin(T& transformable);

// Degree/radian conversion
float			toDegree(float radian);
float			toRadian(float degree);

// Random number generation
int				randomInt(int exclusiveMax);
float           randomFloatNorm();

// Vector operations
float			length(sf::Vector2f vector);
sf::Vector2f	unitVector(sf::Vector2f vector);

// Time format routines
std::string     formatTimeFromSeconds(int seconds);

#include "Utility.inl"
#endif // BOOK_UTILITY_HPP
