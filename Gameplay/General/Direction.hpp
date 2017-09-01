#ifndef DIRECTION_HPP_INCLUDED
#define DIRECTION_HPP_INCLUDED

#include <SFML/System/String.hpp>
#include <sstream>
#include <stdexcept>

namespace Direction
{
    enum Dir
    {
        Up,
        Down,
        Left,
        Right,
        None
    };

    enum Angle
    {
        Front,
        Side,
        Back
    };
}

sf::String         DirToStr(Direction::Dir dir);
Direction::Dir      StrToDir(const sf::String& str);

#endif // DIRECTION_HPP_INCLUDED
