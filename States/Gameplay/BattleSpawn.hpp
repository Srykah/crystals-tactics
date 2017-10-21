#ifndef BATTLESPAWN_HPP_INCLUDED
#define BATTLESPAWN_HPP_INCLUDED

#include "States/Arch/State.hpp"
#include "Gameplay/Battle/BattleContext.hpp"

namespace States
{

class BattleSpawn : public State
{
public:
    BattleSpawn(StateStack* stack, Context context, BattleContext bc);
    ~BattleSpawn();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);

private:
    enum Step
    {
        TileSelection,
        UnitSelection,
        Confirmation
    };

    BattleContext   mBattleContext;
    State*          mChildState;
    Step            mStep;
};


}

#endif // BATTLESPAWN_HPP_INCLUDED
