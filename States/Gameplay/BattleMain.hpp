#ifndef BATTLEMAIN_HPP_INCLUDED
#define BATTLEMAIN_HPP_INCLUDED

#include "States/Arch/State.hpp"
#include "Gameplay/Battle/BattleContext.hpp"

namespace States
{

class BattleMain : public State
{
public:
    BattleMain(StateStack* stack, Context context, BattleContext bc);
    ~BattleMain();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);

private:
    BattleContext       mBattleContext;
};

}

#endif // BATTLEMAIN_HPP_INCLUDED
