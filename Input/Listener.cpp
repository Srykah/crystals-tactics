#include "Input/Listener.hpp"
#include <SFML/Window/Window.hpp>

namespace Input
{
////////////////////////////////////////////////////////////
// Helper function
////////////////////////////////////////////////////////////

StdAction DirToSA(Direction::Dir dir)
{
    switch(dir)
    {
    case Direction::Up:
        return StdAction::Up;

    case Direction::Down:
        return StdAction::Down;

    case Direction::Left:
        return StdAction::Left;

    case Direction::Right:
        return StdAction::Right;
    }

    return StdAction::None;
}

////////////////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////////////////

namespace
{

// Axis and button thresholds. Values found by trial and error ; feel free to experiment
const float AXIS_THRESHOLD = 70.0;
const float BUTTON_THRES = 0.1;

// Axes max value. Found via "std::cout << sf::Joystick::getAxisPosition()" and pushing stick.
// (seems it's in percentage, actually.)
const float AXIS_MAX_VAL = 100.f;

const sf::Time REPEAT_BEGIN = sf::seconds(0.3);
const sf::Time REPEAT_DT = sf::seconds(0.05);

}

////////////////////////////////////////////////////////////
// Listener
////////////////////////////////////////////////////////////

Listener::Listener(sf::Window* window)
: mWindow(window)
, mGamepadID(sf::Joystick::Count)
, mDirection(Direction::None)
, mRepeating(false)
, mAxisUsed(false)
{
    //get the joystick's id
    sf::Joystick::update();
    while (mGamepadID >= 0)
    {
        if (sf::Joystick::isConnected(mGamepadID))
            break;
        else
            mGamepadID--;
    }

    //ZQSD
    mDirectionMap[sf::Keyboard::Z] = Direction::Up;
    mDirectionMap[sf::Keyboard::S] = Direction::Down;
    mDirectionMap[sf::Keyboard::Q] = Direction::Left;
    mDirectionMap[sf::Keyboard::D] = Direction::Right;
    //Arrow keys
    mDirectionMap[sf::Keyboard::Up]     = Direction::Up;
    mDirectionMap[sf::Keyboard::Down]   = Direction::Down;
    mDirectionMap[sf::Keyboard::Left]   = Direction::Left;
    mDirectionMap[sf::Keyboard::Right]  = Direction::Right;

    //D-Pad
    mAxesMap[std::make_pair(sf::Joystick::PovX, true)]  = Direction::Right;
    mAxesMap[std::make_pair(sf::Joystick::PovX, false)] = Direction::Left;
    mAxesMap[std::make_pair(sf::Joystick::PovY, true)]  = Direction::Up;
    mAxesMap[std::make_pair(sf::Joystick::PovY, false)] = Direction::Down;
    //Right stick
    mAxesMap[std::make_pair(sf::Joystick::U, true)]     = Direction::Right;
    mAxesMap[std::make_pair(sf::Joystick::U, false)]    = Direction::Left;
    mAxesMap[std::make_pair(sf::Joystick::R, true)]     = Direction::Down;
    mAxesMap[std::make_pair(sf::Joystick::R, false)]    = Direction::Up;
    //Left stick
    mAxesMap[std::make_pair(sf::Joystick::X, true)]     = Direction::Right;
    mAxesMap[std::make_pair(sf::Joystick::X, false)]    = Direction::Left;
    mAxesMap[std::make_pair(sf::Joystick::Y, true)]     = Direction::Down;
    mAxesMap[std::make_pair(sf::Joystick::Y, false)]    = Direction::Up;

    //emulation of gamepad buttons through keyboard
    mKeyMap[sf::Keyboard::O]        = StdAction::A;
    mKeyMap[sf::Keyboard::P]        = StdAction::B;
    mKeyMap[sf::Keyboard::L]        = StdAction::X;
    mKeyMap[sf::Keyboard::M]        = StdAction::Y;
    mKeyMap[sf::Keyboard::Return]   = StdAction::Start;
    mKeyMap[sf::Keyboard::V]        = StdAction::ZoomOut;
    mKeyMap[sf::Keyboard::N]        = StdAction::ZoomIn;

    //the actual gamepad buttons
    mButtonMap[0] = StdAction::A;
    mButtonMap[1] = StdAction::B;
    mButtonMap[2] = StdAction::X;
    mButtonMap[3] = StdAction::Y;
    mButtonMap[7] = StdAction::Start;
    mButtonMap[4] = StdAction::ZoomOut;
    mButtonMap[5] = StdAction::ZoomIn;
}

void Listener::process(sf::Time delta)
{
    /// we first take care of window events
    sf::Event event;
    while (mWindow->pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed) // if a key is struck
        {
            if (mKeyMap.count(event.key.code))                                              //look for it in the key map
                mQueue.emplace(event, mKeyMap[event.key.code], sf::Mouse::getPosition(*mWindow));

            else if (mDirectionMap.count(event.key.code) && mDirection == Direction::None)  //look for it in the direction map
            {
                mDirection = mDirectionMap[event.key.code];
                mQueue.emplace(event, DirToSA(mDirection), sf::Mouse::getPosition(*mWindow));
            }
            else
                mQueue.emplace(event, None, sf::Mouse::getPosition(*mWindow)); //another key has been struck
        }
        else if (event.type == sf::Event::KeyReleased && !mAxisUsed && mDirection != Direction::None
                 && mDirectionMap.count(event.key.code) && mDirectionMap[event.key.code] == mDirection) //if we release the direction
        {
            mDirection = Direction::None;
            mTimer = sf::Time::Zero;
            mRepeating = false;
        }
        else if (event.type == sf::Event::JoystickButtonPressed && event.joystickButton.joystickId == mGamepadID) // if a button is pressed
        {
            if (mButtonMap.count(event.joystickButton.button))  //look for it in the button map
                mQueue.emplace(event, mButtonMap[event.joystickButton.button], sf::Mouse::getPosition(*mWindow));
            else
                mQueue.emplace(event, None, sf::Mouse::getPosition(*mWindow)); // another button has been pressed
        }

        else if (event.type == sf::Event::JoystickDisconnected && event.joystickConnect.joystickId == mGamepadID) // if the gamepad with focus is disconnected
            mGamepadID = -1;

        else if (event.type == sf::Event::JoystickConnected && mGamepadID != -1) // if a gamepad is connected and we didn't have one, we give it the focus
            mGamepadID = event.joystickConnect.joystickId;

        else
            mQueue.emplace(event, None, sf::Mouse::getPosition(*mWindow));
    }

    sf::Event emptyEvent;
    emptyEvent.type = sf::Event::Count;

    ///we then take care of the axes
    if (mGamepadID != -1)
    {
        if (mDirection == Direction::None) // if no direction is on
        {
            for (auto axe_pair : mAxesMap) // we check if a direction is being triggered
            {
                if ((axe_pair.first.second ? 1.f : -1.f) * sf::Joystick::getAxisPosition(mGamepadID, axe_pair.first.first) >  AXIS_THRESHOLD)
                {
                    mDirection = axe_pair.second;
                    mAxisUsed = true;
                    mQueue.emplace(emptyEvent, DirToSA(mDirection), sf::Mouse::getPosition(*mWindow));
                    break;
                }
            }
        }
        else if (mAxisUsed)//if a direction is on due to an axis
        {
            bool stillTriggered(false); // we have to check if it is still triggered
            for (auto axe_pair : mAxesMap)
            {
                if ((axe_pair.first.second ? 1.f : -1.f) * sf::Joystick::getAxisPosition(mGamepadID, axe_pair.first.first) >  AXIS_THRESHOLD)
                {
                    stillTriggered = true;
                    break;
                }
            }
            if (!stillTriggered)
            {
                mDirection = Direction::None;
                mAxisUsed = false;
                mTimer = sf::Time::Zero;
                mRepeating = false;
            }
        }
    }

    /// we finally check for repeating stuff
    if (mDirection != Direction::None)
    {
        mTimer += delta;

        if (!mRepeating && mTimer >= REPEAT_BEGIN)
        {
            mTimer -= REPEAT_BEGIN;
            mQueue.emplace(emptyEvent, DirToSA(mDirection), sf::Mouse::getPosition(*mWindow));
            mRepeating = true;
        }
        while (mRepeating && mTimer >= REPEAT_DT)
        {
            mTimer -= REPEAT_DT;
            mQueue.emplace(emptyEvent, DirToSA(mDirection), sf::Mouse::getPosition(*mWindow));
        }
    }
}

bool Listener::getEvent(Event& event)
{
    if (!mQueue.empty())
    {
        event = mQueue.front();
        mQueue.pop();
        return true;
    }
    else
        return false;
}

}
