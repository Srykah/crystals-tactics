#ifndef MISSIONSTATE_HPP_INCLUDED
#define MISSIONSTATE_HPP_INCLUDED

#include "../StatesArch/State.hpp"
#include "../Other/pugixml.hpp"

class MissionState : public State
{
public:
    MissionState(StateStack& stack, State::Context& context, const StateData& data);
    ~MissionState();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleInput(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos);
    virtual States::ID  getID() const;

private:
    void loadNextNode();

private:
    bool                    mNothingOpen;
    pugi::xml_document      mDoc;
    pugi::xml_node_iterator mIt;
};

#endif // MISSIONSTATE_HPP_INCLUDED
