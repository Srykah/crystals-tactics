#include "Gameplay/General/Direction.hpp"

sf::String DirToStr(Direction::Dir dir)
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

Direction::Dir StrToDir(const sf::String& str)
{
    if (str == "up") return Direction::Up;
    else if (str == "down") return Direction::Down;
    else if (str == "left") return Direction::Left;
    else if (str == "right") return Direction::Right;
    else if (str == "none") return Direction::None;

    std::stringstream error;
    error << "String " << str.toAnsiString() << " couldn't be converted into Direction::Dir";
    throw std::runtime_error(error.str());
}
