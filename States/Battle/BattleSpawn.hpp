#ifndef BATTLESPAWN_HPP_INCLUDED
#define BATTLESPAWN_HPP_INCLUDED

#include "States/Gameplay/BattleState.hpp"
#include "Gameplay/Battle/BattleContext.hpp"

namespace st
{

class BattleSpawn : public BattleState
{
public:
    BattleSpawn(StateStack* stack, Context context, bt::BattleContext bc);
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

    State*          mChildState;
    Step            mStep;
};


}

#endif // BATTLESPAWN_HPP_INCLUDED
