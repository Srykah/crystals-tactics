#ifndef INPUTHANDLER_HPP_INCLUDED
#define INPUTHANDLER_HPP_INCLUDED

#include <SFML/Window/Event.hpp>
#include <map>
#include <queue>
#include "../Other/Direction.hpp"

struct InputHandler
{
public:
    enum StandardAction
    {
        None,
        Up,
        Down,
        Left,
        Right,
        Start,
        A,
        B,
        X,
        Y
    };

    typedef StandardAction SA;

public:
    InputHandler();

    void processEvent(const sf::Event& event);
    void update(const sf::Time& dt);
    SA getStdAction();

private:
    static const float AXIS_THRESHOLD;
    static const float BUTTON_THRES;
    static const float AXIS_MAX_VAL;
    static const sf::Time REPEAT_BEGIN;
    static const sf::Time REPEAT_DT;

private:
    std::queue<StandardAction> mQueue;
    short mGamepadID;
    sf::Time mRepeatTime;
    short mRepeating;
    Direction::Dir mDirection;
    std::map<sf::Keyboard::Key, SA> mKeyMap;
    std::map<sf::Keyboard::Key, Direction::Dir> mDirectionMap;
    std::map<int, SA> mButtonMap;
    std::map< std::pair<sf::Joystick::Axis, bool>, Direction::Dir > mAxesMap;
};

typedef InputHandler IH;

#endif // INPUTHANDLER_HPP_INCLUDED
