#include "States/Gameplay/UnitSelect.hpp"
#include "Gameplay/Story/Guild.hpp"
#include "Data/ResourceHolder/ResourceIdentifiers.hpp"
#include "Graphism/HUD/Cursor.hpp"
#include "Gameplay/General/Routines.hpp"
#include "States/Gameplay/FacingSelect.hpp"
#include "States/Arch/StateStack.hpp"

namespace st
{

UnitSelect::UnitSelect(StateStack* stack, Context context, bt::BattleContext bc)
: BattleState(stack, context, bc)
, mIndex(0)
, mNode(nullptr)
, mCharacInfo(context, context.guild->getMember(0))
, mChildState(nullptr)
{
    Entities::ID id = CharTypeToEntitiesID(context.guild->getMember(0)->getType());
    gr::Entity* entity = new gr::Entity(context.entities->get(id), "idle", Direction::Down);
    mNode = new gr::EntityNode(entity, bc.cursor->getCoords().y);
    mNode->move(get2DPos(bc.cursor->getCoords()));

    gr::Entity* leftArrow = new gr::Entity(context.entities->get(Entities::Arrow), "float", Direction::Left);
    gr::EntityNode* leftNode = new gr::EntityNode(leftArrow, 0.f, mNode);
    leftNode->move(-TILE_DIM, 0.f);

    gr::Entity* rightArrow = new gr::Entity(context.entities->get(Entities::Arrow), "float", Direction::Right);
    gr::EntityNode* rightNode = new gr::EntityNode(rightArrow, 0.f, mNode);
    rightNode->move(TILE_DIM, 0.f);

    bc.scene->addNode(mNode);
    bc.scene->addNode(leftNode);
    bc.scene->addNode(rightNode);
}

UnitSelect::~UnitSelect()
{

}

void UnitSelect::draw()
{
    mContext.window->draw(mCharacInfo);
}

bool UnitSelect::update(sf::Time dt)
{
    return true;
}

bool UnitSelect::handleEvent(const Input::Event& event)
{
    if (event.stdAc == Input::Left)
    {
        changeCharacter(-1);
        return false;
    }
    else if (event.stdAc == Input::Right)
    {
        changeCharacter(1);
        return false;
    }
    else if (event.stdAc == Input::A)
    {
        mBattleContext.scene->removeNode(mNode);
        Character& unit = *mContext.guild->getMember(mIndex);
        unit.startBattle(mBattleContext, mBattleContext.cursor->getCoords(), Direction::Down);
        mStack->push(new st::FacingSelect(mStack, mContext, mBattleContext, unit, false));
        return false;
    }
    else if (event.stdAc == Input::B)
    {
        mBattleContext.scene->removeNode(mNode);
        closeFailure();
        return false;
    }
    // might add X input to prompt character edit screen

    return true;
}

bool UnitSelect::handleSignal(const Signal& signal)
{
    if (mChildState && signal.sender == mChildState)
    {
        closeSuccess();
        return false;
    }
    return true;
}

void UnitSelect::changeCharacter(short offset)
{
    const int memCount(mContext.guild->getMemberCount());
    mIndex = (mIndex + memCount + offset) % memCount;

    Entities::ID id = CharTypeToEntitiesID(mContext.guild->getMember(mIndex)->getType());
    mNode->entity.reset(new gr::Entity(mContext.entities->get(id), "idle", Direction::Down));

    mCharacInfo.setCharacter(mContext.guild->getMember(mIndex));
}

}
