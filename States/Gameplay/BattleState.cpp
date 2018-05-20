#include "States/Gameplay/BattleState.hpp"

namespace st
{

BattleState::BattleState(StateStack* stack, Context context, BattleContext bc)
: State(stack, context)
, mBattleContext(bc)
{

}

}
