#include "States/Gameplay/BattleSpawn.hpp"
#include "States/Arch/StateStack.hpp"
#include "States/Gameplay/TileSelect.hpp"
#include "States/Gameplay/FreeView.hpp"
#include "States/Gameplay/UnitSelect.hpp"
#include "States/Gameplay/BattleMain.hpp"
#include "States/Menu/OKBox.hpp"

namespace States
{

BattleSpawn::BattleSpawn(StateStack* stack, Context context, BattleContext bc)
: State(stack, context)
, mBattleContext(bc)
, mChildState(new TileSelect(stack, context, bc))
, mStep(UnitSelection)
{
    mStack->push(mChildState, true);
}

BattleSpawn::~BattleSpawn()
{

}

void BattleSpawn::draw()
{

}

bool BattleSpawn::update(sf::Time dt)
{
    return true;
}

bool BattleSpawn::handleEvent(const Input::Event& event)
{
    if ((mStep == Step::TileSelection || mStep == Step::FreeViewing) && event.stdAc == Input::X)
    {
        mStack->close(mChildState);
        mChildState = new OKBox(mStack, mContext, "Lancer le combat ?");
        mStack->push(mChildState);
        mStep = Confirmation;

        return false;
    }

    return true;
}

bool BattleSpawn::handleSignal(const Signal& signal)
{
    if (signal.sender == mChildState)
    {
        switch(mStep)
        {
        case Step::TileSelection:
            if (boost::get<bool>(signal.data)) // if we have selected a tile
            {
                mStep = Step::UnitSelection;
                mChildState = new UnitSelect(mStack, mContext, mBattleContext);
                mStack->push(mChildState);
            }
            else // if we leave the tile selection, open free view
            {
                mStep = Step::FreeViewing;
                mChildState = new FreeView(mStack, mContext, mBattleContext);
                mStack->push(mChildState);
            }
            return false;

        case Step::UnitSelection:
        case Step::FreeViewing:
            mStep = Step::TileSelection;
            mChildState = new TileSelect(mStack, mContext, mBattleContext);
            mStack->push(mChildState);
            return false;

        case Step::Confirmation:
            if (boost::get<bool>(signal.data)) // start battle
            {
                mStack->push(new BattleMain(mStack, mContext, mBattleContext));
            }
            else // back to selecting a tile
            {
                mStep = Step::TileSelection;
                mChildState = new TileSelect(mStack, mContext, mBattleContext);
                mStack->push(mChildState);
            }
            return false;
        }
    }

    return true;
}

}
