#ifndef BATTLESTATE_HPP_INCLUDED
#define BATTLESTATE_HPP_INCLUDED

#include "States/Arch/State.hpp"
#include "Gameplay/Battle/BattleContext.hpp"

namespace st
{

class BattleState : public State
{
public:
    BattleState(StateStack* stack, Context context, bt::BattleContext bc);
    ~BattleState() = default;

protected:
    bt::BattleContext mBattleContext;
};


}

#endif // BATTLESTATE_HPP_INCLUDED
