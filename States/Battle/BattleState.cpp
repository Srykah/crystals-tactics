#include "States/Gameplay/BattleState.hpp"

namespace st
{

BattleState::BattleState(StateStack* stack, Context context, bt::BattleContext bc)
: State(stack, context)
, mBattleContext(bc)
{

}

}
