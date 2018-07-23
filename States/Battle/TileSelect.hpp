#ifndef TILESELECT_HPP_INCLUDED
#define TILESELECT_HPP_INCLUDED

#include "States/Gameplay/BattleState.hpp"
#include "Gameplay/Battle/BattleContext.hpp"

namespace st
{

class TileSelect : public BattleState
{
public:
    TileSelect(StateStack* stack, Context context, bt::BattleContext bc, bool freeViewing = false);
    ~TileSelect();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);

private:
    bt::BattleContext       mBattleContext;
    bool                mFreeViewing;
};

}

#endif // TILESELECT_HPP_INCLUDED
