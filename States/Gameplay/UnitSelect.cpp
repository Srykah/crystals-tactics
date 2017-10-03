#include "States/Gameplay/UnitSelect.hpp"

namespace States
{

UnitSelect::UnitSelect(StateStack* stack, Context context, BattleContext bc)
: State(stack, context)
, mBattleContext(bc)
{

}

UnitSelect::~UnitSelect()
{

}

void UnitSelect::draw()
{

}

bool UnitSelect::update(sf::Time dt)
{

}

bool UnitSelect::handleEvent(const Input::Event& event)
{

}

bool UnitSelect::handleSignal(const Signal& signal)
{

}


}
