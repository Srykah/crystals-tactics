#ifndef TILESELECT_HPP_INCLUDED
#define TILESELECT_HPP_INCLUDED

#include "States/Arch/State.hpp"
#include "Gameplay/Battle/BattleContext.hpp"

namespace States
{

class TileSelect : public State
{
public:
    TileSelect(StateStack* stack, Context context, BattleContext bc, bool freeViewing = false);
    ~TileSelect();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);

private:
    BattleContext       mBattleContext;
    bool                mFreeViewing;
};

}

#endif // TILESELECT_HPP_INCLUDED
