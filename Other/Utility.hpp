#ifndef UTILITY_HPP_INCLUDED
#define UTILITY_HPP_INCLUDED

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/String.hpp>

#include <sstream>
#include <type_traits>
#include <vector>

namespace sf
{
	class Sprite;
}

namespace gr
{
    class Animation;
    class Text;
}

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
sf::String		ToStr(const T& value);

// Convert enumerators to strings
sf::String		KeyToStr(sf::Keyboard::Key key);

// Call setOrigin() with the center of the object
template <typename T>
void			centerOrigin(T& transformable);

// Degree/radian conversion
float			RadianToDegree(float radian);
float			DegreeToRadian(float degree);

// Random number generation
int				randomInt(int exclusiveMax);
float           randomFloatNorm();
float           randomPick(int val);

// Vector operations
float			length(sf::Vector2f vector);
sf::Vector2f	unitVector(sf::Vector2f vector);
int             scal(int x1, int y1, int x2, int y2);

// Arithmetics
int signe(int val);

// Time format routines
sf::String     SecondsToStr(int seconds);

// Enum class -> int conversions
template<typename Enum>
constexpr auto toInt(Enum e);

template<typename Enum>
std::vector<short> getRange();

template<typename T>
using Grid = std::vector< std::vector< T > >;

#include "Utility.inl"
#endif // UTILITY_HPP_INCLUDED
