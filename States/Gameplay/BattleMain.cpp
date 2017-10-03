#include "States/Gameplay/BattleMain.hpp"

namespace States
{

BattleMain::BattleMain(StateStack* stack, Context context, BattleContext bc)
: State(stack, context)
, mBattleContext(bc)
{

}

BattleMain::~BattleMain()
{

}

void BattleMain::draw()
{

}

bool BattleMain::update(sf::Time dt)
{

}

bool BattleMain::handleEvent(const Input::Event& event)
{

}

bool BattleMain::handleSignal(const Signal& signal)
{

}


}
