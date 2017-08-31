#ifndef DIRECTION_HPP_INCLUDED
#define DIRECTION_HPP_INCLUDED

#include <string>
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

std::string         DirToStr(Direction::Dir dir);
Direction::Dir      StrToDir(const std::string& str);

#endif // DIRECTION_HPP_INCLUDED
