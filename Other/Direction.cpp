#include "../Other/Direction.hpp"

Direction::Dir stringToDir(std::string str)
{
    if (str == "up") return Direction::Up;
    else if (str == "down") return Direction::Down;
    else if (str == "left") return Direction::Left;
    else if (str == "right") return Direction::Right;

    std::stringstream error;
    error << "String " << str << " couldn't be converted into Direction::Dir";
    throw std::runtime_error(error.str());
}
