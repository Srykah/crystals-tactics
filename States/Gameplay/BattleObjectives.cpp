#include "States/Gameplay/BattleObjectives.hpp"
#include "States/Arch/StateStack.hpp"
#include "States/Gameplay/BattleSpawn.hpp"
#include "Gameplay/Battle/Battlefield.hpp"
#include "Other/Utility.hpp"

namespace States
{

BattleObjectives::BattleObjectives(StateStack* stack, Context context, BattleContext bc)
: State(stack, context)
, mBattleContext(bc)
, mText("Battez tous les ennemis !", context.fonts->get(Fonts::Main), 60, Graphism::Text::Shadow, sf::Color::Red)
{
    sf::Vector2f taille(TILE_DIM * mBattleContext.bf->getGridSize());
    sf::Vector2f centre = taille / 2.f;
    if (taille.x / taille.y < 16.f/9.f)
    {
        taille.y += 2*TILE_DIM;
        taille.x = 16.f/9.f*taille.y;
    }
    else
    {
        taille.x += 2*TILE_DIM;
        taille.y = taille.x*9.f/16.f;
    }
    *mBattleContext.view = sf::View(centre, taille);

    centerOrigin(mText);
    mText.setPosition(683.f, 384.f);
}

BattleObjectives::~BattleObjectives()
{

}

void BattleObjectives::draw()
{
    mContext.window->draw(mText);
}

bool BattleObjectives::update(sf::Time dt)
{
    return true;
}

bool BattleObjectives::handleEvent(const Input::Event& event)
{
    if (event.stdAc == Input::A)
    {
        *mBattleContext.step = BattleStep::Spawn;
        mStack->push(new BattleSpawn(mStack, mContext, mBattleContext), true);
        mStack->close(this);
    }
}

bool BattleObjectives::handleSignal(const Signal& signal)
{
    return true;
}

}
