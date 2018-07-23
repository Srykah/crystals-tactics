#include "States/Battle/BattleLoop.hpp"

namespace bs
{

BattleLoop::BattleLoop(sa::StateStack* stack, sa::Context context, bt::BattleContext bc)
: BattleState(stack, context, bc)
{

}

BattleLoop::~BattleLoop()
{

}

void BattleLoop::draw()
{

}

bool BattleLoop::update(sf::Time dt)
{
    if (mBattleContext.cutscene.isEmpty() && mBattleContext.ul.waiting())
    {
        if (mBattleContext.ul.battleWon())
            closeSuccess();
        else if (mBattleContext.ul.battleLost())
            closeFailure();
        else
        {
            Character* unit(nullptr);
            while (!(unit = mBattleContext.ul.getReadyUnit()))
            {
                mBattleContext.ul.
            }
        }
    }
}

bool BattleLoop::handleEvent(const Input::Event& event)
{

}

bool BattleLoop::handleSignal(const Signal& signal)
{

}


}
