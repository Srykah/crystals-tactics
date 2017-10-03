#include "States/Gameplay/TileSelect.hpp"
#include "States/Arch/StateStack.hpp"
#include "Gameplay/Battle/Battlefield.hpp"
#include "Graphism/HUD/Cursor.hpp"

namespace States
{

TileSelect::TileSelect(StateStack* stack, Context context, BattleContext bc)
: State(stack, context)
, mBattleContext(bc)
{
    bc.bf->highlightSpawns();
    bc.cursor->setVisible();
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
        if (mBattleContext.bf->isHighlighted(mBattleContext.cursor->getCoords()))
        {
            emit(true);
            mStack->close(this);
            mBattleContext.bf->clearPaint();
            mBattleContext.cursor->setVisible(false);
        }
        return false;

    case Input::B:
        emit(false);
        mStack->close(this);
        mBattleContext.bf->clearPaint();
        mBattleContext.cursor->setVisible(false);
        return false;

    case Input::Left:
        mBattleContext.cursor->move(sf::Vector2i(-1,0));
        return false;

    case Input::Right:
        mBattleContext.cursor->move(sf::Vector2i(1,0));
        return false;

    case Input::Up:
        mBattleContext.cursor->move(sf::Vector2i(0,-1));
        return false;

    case Input::Down:
        mBattleContext.cursor->move(sf::Vector2i(0,1));
        return false;
    }

    return true;
}

bool TileSelect::handleSignal(const Signal& signal)
{
    return true;
}

}
