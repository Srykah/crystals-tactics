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
        Right
    };
}

Direction::Dir stringToDir(std::string str);

#endif // DIRECTION_HPP_INCLUDED
