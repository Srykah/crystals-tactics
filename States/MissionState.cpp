#include "../States/MissionState.hpp"

MissionState::MissionState(StateStack& stack, State::Context& context, const StateData& data)
: State(stack, context)
{
    if(!mDoc.load_file(data.str().c_str()))
        throw std::runtime_error("mission file " + data.str() + " failed to load / parse.");

    mIt = mDoc.child("mission").begin();

    std::string nodeName(mIt->name());
    if (nodeName == std::string("dialog"))
        requestStackPush(States::MissionDialog, *mIt, true);
    else if (nodeName == std::string("battle"))
        requestStackPush(States::Battle, *mIt, true);
}

MissionState::~MissionState()
{

}

void MissionState::draw()
{

}

bool MissionState::update(sf::Time dt)
{
    if (std::string(mIt->name()) == std::string("battle") && getData(States::Battle).getDataType() == StateData::Boolean)
    {
        if (getData(States::Battle).boolean())
            loadNextNode();
        else
        {
            setData(false);
            requestStackClose();
        }
    }
    else if (std::string(mIt->name()) == std::string("dialog") && getData(States::MissionDialog).getDataType() == StateData::Boolean)
    {
        if (getData(States::MissionDialog).boolean())
            loadNextNode();
        else
        {
            setData(false);
            requestStackClose();
        }
    }

    return false;
}

bool MissionState::handleInput(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos)
{
    return false;
}

States::ID MissionState::getID() const
{
    return States::Mission;
}

void MissionState::loadNextNode()
{
    mIt++;

    if (mIt == mDoc.children().end())
    {
        setData(true);
        requestStackClear();
        // requestStackPush(States::WorldMap);
    }
    else
    {
        std::string nodeName(mIt->name());
        if (nodeName == std::string("dialog"))
            requestStackPush(States::MissionDialog, *mIt);
        else if (nodeName == std::string("battle"))
            requestStackPush(States::Battle, *mIt);
    }
}
