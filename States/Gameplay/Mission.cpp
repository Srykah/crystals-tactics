#include "States/Gameplay/Mission.hpp"
#include "States/Arch/StateStack.hpp"
#include "States/Gameplay/BattleMain.hpp"
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
    forward();
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
    if (signal.sender == )
    return false;
}

void Mission::forward()
{
    if (sf::String(mNode.name()) == sf::String("dialog"))
        mStack->push(new MissionDialogue(mStack, mContext, mNode));
    else if (sf::String(mNode.name()) == sf::String("battle"))
        mStack->push(new BattleMain(mStack, mContext, mNode), true);
    else throw std::runtime_error("mission file corrupted");
}

}
