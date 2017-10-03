#ifndef FREEVIEW_HPP_INCLUDED
#define FREEVIEW_HPP_INCLUDED

#include "States/Arch/State.hpp"
#include "Gameplay/Battle/BattleContext.hpp"

namespace States
{

class FreeView : public State
{
public:
    FreeView(StateStack* stack, Context context, BattleContext bc);
    ~FreeView();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);

private:
    BattleContext       mBattleContext;
};

}

#endif // FREEVIEW_HPP_INCLUDED
