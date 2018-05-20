#ifndef BATTLEOBJECTIVESSTATE_HPP_INCLUDED
#define BATTLEOBJECTIVESSTATE_HPP_INCLUDED

#include "States/Gameplay/BattleState.hpp"
#include "Gameplay/Battle/BattleContext.hpp"
#include "Graphism/Text.hpp"

namespace st
{

class BattleObjectives : public BattleState
{
public:
    BattleObjectives(StateStack* stack, Context context, BattleContext bc);
    ~BattleObjectives();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);

private:
    gr::Text  mText;
};

}

#endif // BATTLEOBJECTIVESSTATE_HPP_INCLUDED
