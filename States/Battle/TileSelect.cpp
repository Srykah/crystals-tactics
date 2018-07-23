#include "States/Gameplay/TileSelect.hpp"
#include "States/Arch/StateStack.hpp"
#include "Gameplay/Battle/Battlefield.hpp"
#include "Graphism/HUD/Cursor.hpp"

namespace st
{

TileSelect::TileSelect(StateStack* stack, Context context, bt::BattleContext bc, bool freeViewing)
: BattleState(stack, context, bc)
, mFreeViewing(freeViewing)
{
    bc.cursor->setVisible();

    *bc.view = bc.cursor->getView(1.f);
}

TileSelect::~TileSelect()
{

}

void TileSelect::draw()
{

}

bool TileSelect::update(sf::Time dt)
{
    return true;
}

bool TileSelect::handleEvent(const Input::Event& event)
{
    switch (event.stdAc)
    {
    case Input::A:
        if (!mFreeViewing && mBattleContext.bf->isHighlighted(mBattleContext.cursor->getCoords()))
        {
            mBattleContext.cursor->setVisible(false);
            closeSuccess();
        }
        return false;

    case Input::B:
        mBattleContext.cursor->setVisible(false);
        closeFailure();
        return false;

    case Input::Left:
        mBattleContext.cursor->move(sf::Vector2i(-1,0));
        *mBattleContext.view = mBattleContext.cursor->getView(1.f);
        return false;

    case Input::Right:
        mBattleContext.cursor->move(sf::Vector2i(1,0));
        *mBattleContext.view = mBattleContext.cursor->getView(1.f);
        return false;

    case Input::Up:
        mBattleContext.cursor->move(sf::Vector2i(0,-1));
        *mBattleContext.view = mBattleContext.cursor->getView(1.f);
        return false;

    case Input::Down:
        mBattleContext.cursor->move(sf::Vector2i(0,1));
        *mBattleContext.view = mBattleContext.cursor->getView(1.f);
        return false;
    }

    return true;
}

bool TileSelect::handleSignal(const Signal& signal)
{
    return true;
}

}
