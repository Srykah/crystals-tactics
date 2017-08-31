#include "States/Gameplay/Mission.hpp"
#include "States/Arch/StateStack.hpp"
#include "States/Gameplay/Battle.hpp"
#include "States/Menu/MissionDialogue.hpp"
#include <stdexcept>

namespace States
{

Mission::Mission(StateStack* stack, Context context, const std::string& filename)
: State(stack, context)
, mFirst(true)
{
    if(!mDoc.load_file(filename.c_str()))
        throw std::runtime_error("mission file " + filename + " failed to load / parse.");
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
    if (mFirst)
        beginMission();

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
    mFirst = false;

    pugi::xml_node firstNode(mDoc.child("mission").first_child());
    if (std::string(firstNode.name()) == std::string("dialog"))
        mStack->push(new MissionDialogue(mStack, mContext, firstNode));
    else if (std::string(firstNode.name()) == std::string("battle"))
        mStack->push(new Battle(mStack, mContext, firstNode));
    else throw std::runtime_error("failed to begin mission");
}

}
