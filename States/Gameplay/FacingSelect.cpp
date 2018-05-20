#include "States/Gameplay/FacingSelect.hpp"
#include "Gameplay/Character/Character.hpp"
#include "Gameplay/General/Routines.hpp"
#include "Graphism/Scene/Scene.hpp" //i don't know why i need this here
#include "States/Arch/StateStack.hpp" //this neither

namespace st
{

FacingSelect::FacingSelect(StateStack* stack, Context context, BattleContext bc, Character& unit, bool cancellable)
: BattleState(stack, context, bc)
, mNode(new gr::EmptyNode(100.f))
, mUnit(unit)
, mInitialFacing(unit.getFacing())
, mCancellable(cancellable)
{
    mNode->setPosition(get2DPos(unit.getCoords()));

    gr::Entity* leftArrow = new gr::Entity(context.entities->get(Entities::Arrow), "float", Direction::Left);
    gr::EntityNode* leftNode = new gr::EntityNode(leftArrow, 0.f, mNode);
    leftNode->move(-2.f * TILE_DIM, 0.f);

    gr::Entity* rightArrow = new gr::Entity(context.entities->get(Entities::Arrow), "float", Direction::Right);
    gr::EntityNode* rightNode = new gr::EntityNode(rightArrow, 0.f, mNode);
    rightNode->move(2.f * TILE_DIM, 0.f);

    gr::Entity* upArrow = new gr::Entity(context.entities->get(Entities::Arrow), "float", Direction::Up);
    gr::EntityNode* upNode = new gr::EntityNode(upArrow, 0.f, mNode);
    upNode->move(0.f, -2.f * TILE_DIM);

    gr::Entity* downArrow = new gr::Entity(context.entities->get(Entities::Arrow), "float", Direction::Down);
    gr::EntityNode* downNode = new gr::EntityNode(downArrow,  0.f, mNode);
    downNode->move(0.f, 2.f * TILE_DIM);

    bc.scene->addNode(mNode);
    bc.scene->addNode(leftNode);
    bc.scene->addNode(rightNode);
    bc.scene->addNode(upNode);
    bc.scene->addNode(downNode);
}

void FacingSelect::draw()
{

}

bool FacingSelect::update(sf::Time dt)
{
    return true;
}

bool FacingSelect::handleEvent(const Input::Event& event)
{
    if (event.stdAc == Input::Left)
        mUnit.setFacing(Direction::Left);
    else if (event.stdAc == Input::Right)
        mUnit.setFacing(Direction::Right);
    else if (event.stdAc == Input::Up)
        mUnit.setFacing(Direction::Up);
    else if (event.stdAc == Input::Down)
        mUnit.setFacing(Direction::Down);
    else if (event.stdAc == Input::A)
    {
        mBattleContext.scene->removeNode(mNode);
        mStack->close(this);
        emit(true);
    }
    else if (mCancellable && event.stdAc == Input::B)
    {
        mBattleContext.scene->removeNode(mNode);
        mUnit.setFacing(mInitialFacing);
        mStack->close(this);
        emit(false);
    }
    else
        return true;
    return false;
}

bool FacingSelect::handleSignal(const Signal& signal)
{
    return true;
}

}

