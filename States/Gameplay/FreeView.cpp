#include "States/Gameplay/FreeView.hpp"

namespace States
{

FreeView::FreeView(StateStack* stack, Context context, BattleContext bc)
: State(stack, context)
, mBattleContext(bc)
{

}

FreeView::~FreeView()
{

}

void FreeView::draw()
{

}

bool FreeView::update(sf::Time dt)
{

}

bool FreeView::handleEvent(const Input::Event& event)
{

}

bool FreeView::handleSignal(const Signal& signal)
{

}


}
