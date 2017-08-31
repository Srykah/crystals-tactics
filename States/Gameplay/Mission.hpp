#ifndef MISSIONSTATE_HPP_INCLUDED
#define MISSIONSTATE_HPP_INCLUDED

#include "States/Arch/State.hpp"
#include "XML/pugixml.hpp"

namespace States
{

class Mission : public State
{
public:
    Mission(StateStack* stack, Context context, const std::string& filename);
    ~Mission();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);

private:
    void beginMission();

private:
    pugi::xml_document      mDoc;
};

}

#endif // MISSIONSTATE_HPP_INCLUDED
