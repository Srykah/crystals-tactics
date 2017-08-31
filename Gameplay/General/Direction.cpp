#include "Gameplay/General/Direction.hpp"

std::string DirToStr(Direction::Dir dir)
{
    switch(dir)
    {
    case Direction::Up:
        return "up";
    case Direction::Down:
        return "down";
    case Direction::Left:
        return "left";
    case Direction::Right:
        return "right";
    default:
        return "none";
    }
}

Direction::Dir StrToDir(const std::string& str)
{
    if (str == "up") return Direction::Up;
    else if (str == "down") return Direction::Down;
    else if (str == "left") return Direction::Left;
    else if (str == "right") return Direction::Right;
    else if (str == "none") return Direction::None;

    std::stringstream error;
    error << "String " << str << " couldn't be converted into Direction::Dir";
    throw std::runtime_error(error.str());
}
