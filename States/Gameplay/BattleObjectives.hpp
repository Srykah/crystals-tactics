#ifndef BATTLEOBJECTIVESSTATE_HPP_INCLUDED
#define BATTLEOBJECTIVESSTATE_HPP_INCLUDED

#include "States/Arch/State.hpp"
#include "Gameplay/Battle/BattleContext.hpp"
#include "Graphism/Text.hpp"

namespace States
{

class BattleObjectives : public State
{
public:
    BattleObjectives(StateStack* stack, Context context, BattleContext bc);
    ~BattleObjectives();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);

private:
    BattleContext   mBattleContext;
    Graphism::Text  mText;
};

}

#endif // BATTLEOBJECTIVESSTATE_HPP_INCLUDED
