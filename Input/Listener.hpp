#ifndef INTERPRETER_HPP_INCLUDED
#define INTERPRETER_HPP_INCLUDED

#include <SFML/Window/Event.hpp>
#include <map>
#include <queue>
#include "Gameplay/General/Direction.hpp"
#include "Input/Event.hpp"

namespace Input
{

struct Listener
{
public:
    Listener(sf::Window* window);

    void process(sf::Time delta);
    bool getEvent(Event& event);

private:
    sf::Window* mWindow;
    std::queue<Event> mQueue;
    short mGamepadID;

    std::map<sf::Keyboard::Key, StdAction> mKeyMap;
    std::map<sf::Keyboard::Key, Direction::Dir> mDirectionMap;
    std::map<int, StdAction> mButtonMap;
    std::map< std::pair<sf::Joystick::Axis, bool>, Direction::Dir > mAxesMap;

    Direction::Dir mDirection;
    sf::Time mTimer;
    bool mRepeating;
    bool mAxisUsed;
};

}

#endif // INTERPRETER_HPP_INCLUDED
