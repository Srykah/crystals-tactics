#ifndef MISSIONSTATE_HPP_INCLUDED
#define MISSIONSTATE_HPP_INCLUDED

#include "States/Arch/State.hpp"
#include "XML/pugixml.hpp"

namespace st
{

class Mission : public State
{
public:
    Mission(StateStack* stack, Context context, const sf::String& filename);
    ~Mission();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);

private:
    void                readStep();

private:
    pugi::xml_document      mDoc;
    pugi::xml_node          mNode;
    st::State*              mChildState;
};

}

#endif // MISSIONSTATE_HPP_INCLUDED
