#include "States/Gameplay/Mission.hpp"
#include "States/Arch/StateStack.hpp"
#include "States/Gameplay/Battle.hpp"
#include "States/Menu/MissionDialogue.hpp"
#include <stdexcept>

namespace States
{

Mission::Mission(StateStack* stack, Context context, const sf::String& filename)
: State(stack, context)
{
    if(!mDoc.load_file(filename.toAnsiString().c_str()))
        throw std::runtime_error("mission file " + filename + " failed to load / parse.");

    beginMission();
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
    return false;
}

void Mission::beginMission()
{
    pugi::xml_node firstNode(mDoc.child("mission").first_child());
    if (sf::String(firstNode.name()) == sf::String("dialog"))
        mStack->push(new MissionDialogue(mStack, mContext, firstNode));
    else if (sf::String(firstNode.name()) == sf::String("battle"))
        mStack->push(new Battle(mStack, mContext, firstNode), true);
    else throw std::runtime_error("failed to begin mission");
}

}
