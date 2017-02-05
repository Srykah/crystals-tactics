#include "../Input/InputHandler.hpp"

////////////////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////////////////

// Axis and button thresholds. Values found by trial and error ; feel free to experiment
const float IH::AXIS_THRESHOLD = 70.0;
const float IH::BUTTON_THRES = 0.1;

// Axes max value. Found via "std::cout << sf::Joystick::getAxisPosition()" and pushing stick.
// (seems it's in percentage, actually.)
const float IH::AXIS_MAX_VAL = 100.f;

const sf::Time IH::REPEAT_BEGIN = sf::seconds(0.3);
const sf::Time IH::REPEAT_DT = sf::seconds(0.05);

////////////////////////////////////////////////////////////
// InputHandler
////////////////////////////////////////////////////////////

InputHandler::InputHandler()
: mRepeating(0)
, mDirection(Direction::Down)
{
    // get the joystick's id
    sf::Joystick::update();
    bool gamepadConnected(false);
    int i(0);
    while (!gamepadConnected && i < sf::Joystick::Count)
    {
        gamepadConnected = sf::Joystick::isConnected(i);
        i++;
    }
    mGamepadID = i-1;

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
    mKeyMap[sf::Keyboard::O]        = SA::A;
    mKeyMap[sf::Keyboard::P]        = SA::B;
    mKeyMap[sf::Keyboard::L]        = SA::X;
    mKeyMap[sf::Keyboard::M]        = SA::Y;
    mKeyMap[sf::Keyboard::Return]   = SA::Start;

    //the actual gamepad buttons
    mButtonMap[0] = SA::A;
    mButtonMap[1] = SA::B;
    mButtonMap[2] = SA::X;
    mButtonMap[3] = SA::Y;
    mButtonMap[7] = SA::Start;
}

void InputHandler::processEvent(const sf::Event& event)
{
    // if a key is struck
    if (event.type == sf::Event::KeyPressed)
    {
        //look for it in the key map
        auto it = mKeyMap.find(event.key.code);
        if (it != mKeyMap.end())
            mQueue.push(it->second);
    }
    // if a button (from the right joystick) is pressed
    else if (event.type == sf::Event::JoystickButtonPressed && event.joystickButton.joystickId == mGamepadID)
    {
        //look for it in the button map
        auto it = mButtonMap.find(event.joystickButton.button);
        if (it != mButtonMap.end())
            mQueue.push(it->second);
    }
    // if the gamepad with focus is disconnected
    else if (event.type == sf::Event::JoystickDisconnected && event.joystickConnect.joystickId == mGamepadID)
    {
        // we check for a new one (see above)
        for (int i(sf::Joystick::Count -1); i >= 0; i--)
        {
            if (sf::Joystick::isConnected(i))
                mGamepadID = i;
        }
    }
    // if a gamepad is connected and we didn't have one, we give it the focus
    else if (event.type == sf::Event::JoystickConnected && mGamepadID != -1)
        mGamepadID = event.joystickConnect.joystickId;
}

void InputHandler::update(const sf::Time& dt)
{
    // we take care of axes here ; that is, we look for directions

    // we check for each direction if something triggers it
    std::map<Direction::Dir, bool> tab;
    tab[Direction::Up]      = false;
    tab[Direction::Down]    = false;
    tab[Direction::Left]    = false;
    tab[Direction::Right]   = false;

    // first, keyboard
    for (auto pr : mDirectionMap)
        tab[pr.second] = tab[pr.second] || sf::Keyboard::isKeyPressed(pr.first);

    // then, the gamepad's axes (if some gamepad has focus)
    for (auto pr : mAxesMap)
        tab[pr.second] = tab[pr.second]
        || ((pr.first.second && sf::Joystick::getAxisPosition(mGamepadID, pr.first.first) > AXIS_THRESHOLD)
            || (!pr.first.second && sf::Joystick::getAxisPosition(mGamepadID, pr.first.first) < -AXIS_THRESHOLD));

    // now, we look if we're not moving but some direction is on (d>u>r>l)
    if (mRepeating == 0 && (tab[Direction::Up] || tab[Direction::Down] || tab[Direction::Left] || tab[Direction::Right]))
    {
        // in which case we queue up the stdAc, we put the repeating on phase 1
        // and we update the current direction.
        if (tab[Direction::Right])
        {
            mQueue.push(SA::Right);
            mDirection = Direction::Right;
        }
        else if (tab[Direction::Left])
        {
            mQueue.push(SA::Left);
            mDirection = Direction::Left;
        }

        if (tab[Direction::Down])
        {
            mQueue.push(SA::Down);
            mDirection = Direction::Down;
        }
        else if (tab[Direction::Up])
        {
            mQueue.push(SA::Up);
            mDirection = Direction::Up;
        }

        mRepeating = 1;
    }

    // now, we look if we're waiting for repeat.
    if (mRepeating == 1)
    {
        mRepeatTime += dt;

        // if the current direction is still on :
        if (tab[mDirection])
        {
            // if time has passed enough : we queue up the stdAc and we put the repeat on phase 2.
            if (mRepeatTime > REPEAT_BEGIN)
            {
                if (mDirection == Direction::Down)
                    mQueue.push(SA::Down);
                else if (mDirection == Direction::Up)
                    mQueue.push(SA::Up);
                else if (mDirection == Direction::Right)
                    mQueue.push(SA::Right);
                else if (mDirection == Direction::Left)
                    mQueue.push(SA::Left);

                mRepeating = 2;
                mRepeatTime -= REPEAT_BEGIN;
            }
        }
        // if it's not, we check if another direction is active (d>u>r>l).
        else
        {
            // if we find one, we update the current direction to it.
            if (tab[Direction::Up] || tab[Direction::Down] || tab[Direction::Left] || tab[Direction::Right])
            {
                if (tab[Direction::Down])
                    mDirection = Direction::Down;
                else if (tab[Direction::Up])
                    mDirection = Direction::Up;
                else if (tab[Direction::Right])
                    mDirection = Direction::Right;
                else if (tab[Direction::Left])
                    mDirection = Direction::Left;
            }
            // if we don't find one, we put repeat to phase 0 and we reset the timer.
            else
            {
                mRepeating = 0;
                mRepeatTime = sf::Time::Zero;
            }
        }
    }

    // now, we look if we're repeating.
    else if (mRepeating == 2)
    {
        mRepeatTime += dt;

        // if the current direction is still on :
        if (tab[mDirection])
        {
            // if time has passed enough, as long as we have time left,
            while (mRepeatTime > REPEAT_DT)
            {
                // we queue up the stdAc and we decrement the timer.
                if (mDirection == Direction::Down)
                    mQueue.push(SA::Down);
                else if (mDirection == Direction::Up)
                    mQueue.push(SA::Up);
                else if (mDirection == Direction::Right)
                    mQueue.push(SA::Right);
                else if (mDirection == Direction::Left)
                    mQueue.push(SA::Left);

                mRepeatTime -= REPEAT_DT;
            }
        }
        // if it's not, we check if another direction is active (d>u>r>l).
        else
        {
            // if we find one, we update the current direction to it.
            if (tab[Direction::Up] || tab[Direction::Down] || tab[Direction::Left] || tab[Direction::Right])
            {
                if (tab[Direction::Down])
                    mDirection = Direction::Down;
                else if (tab[Direction::Up])
                    mDirection = Direction::Up;
                else if (tab[Direction::Right])
                    mDirection = Direction::Right;
                else if (tab[Direction::Left])
                    mDirection = Direction::Left;
            }
            // if we don't find one, we put repeat to phase 0 and we reset the timer.
            else
            {
                mRepeating = 0;
                mRepeatTime = sf::Time::Zero;
            }
        }
    }
}

IH::SA InputHandler::getStdAction()
{
    if (!mQueue.empty())
    {
        SA stdAc = mQueue.front();
        mQueue.pop();
        return stdAc;
    }
    else
        return SA::None;
}
