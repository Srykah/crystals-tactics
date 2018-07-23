#include "States/Gameplay/Mission.hpp"
#include "States/Arch/StateStack.hpp"
#include "States/Gameplay/BattleBackground.hpp"
#include "States/Menu/MissionDialogue.hpp"
#include <stdexcept>

namespace st
{

Mission::Mission(StateStack* stack, Context context, const sf::String& filename)
: State(stack, context)
{
    if(!mDoc.load_file(filename.toAnsiString().c_str()))
        throw std::runtime_error("mission file " + filename + " failed to load / parse.");

    mNode = mDoc.child("mission").first_child();
    readStep();
}

Mission::~Mission()
{

}

void Mission::draw()
{
    /*
    sf::RectangleShape shape(sf::Vector2f(60.f, 60.f));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(653.f, 304.f);
    mContext.window->draw(shape);
    */
}

bool Mission::update(sf::Time dt)
{
    return false;
}

bool Mission::handleEvent(const Input::Event& event)
{
    return false;
}

bool Mission::handleSignal(const Signal& signal)
{
    if (signal.sender == mChildState)
    {
        if (boost::get<bool>(signal.data)) // advance mission
        {
            mNode = mNode.next_sibling();
            if (mNode)
                readStep();
            else // mission finished : success
                closeSuccess();
        }
        else // game over
            closeFailure();
    }
    return false;
}

void Mission::readStep()
{
    if (sf::String(mNode.name()) == sf::String("dialog"))
        mChildState = new MissionDialogue(mStack, mContext, mNode);
    else if (sf::String(mNode.name()) == sf::String("battle"))
        mChildState = new BattleBackground(mStack, mContext, mNode);
    else
        throw std::runtime_error("mission file corrupted");

    mStack->push(mChildState, true);
}

}
