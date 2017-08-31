#include "States/GameplayStates/BattleState.hpp"
#include "Gameplay/Mission/Guild.hpp"
#include "Gameplay/GameplayUtility.hpp"
#include "Graphism/Node.hpp"
#include <cassert>
#include <algorithm>

void BattleState::handleInputUnitPlacing(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos)
{
    if (mStep == TileSelect)
    {
        if (stdAction == IH::A)
        {
            if (mBattlefield.isSpawn(mCursorCoords))
            {
                mStep = CharacterSelect;
                mBattlefield.showSpawns(false);

                auto charac = mUnitList.getUnitByTile(mCursorCoords);
                if (charac != nullptr)
                    charac->endBattle();

                mSelection = 0;

                mEntity = *getContext().guild->getMember(mSelection)->getEntity();
                mEntity.setAnimationAndFacing(Graphism::Animations::Idle, Direction::Down);
                Graphism::Node entityNode(&mEntity, mCursorCoords.y);
                entityNode.setPosition(get2DPos(mCursorCoords));
                mScene.addNode(entityNode);

                mArrows[Direction::Left].setPosition(30, 384);
                mArrows[Direction::Right].setPosition(1336, 384);

                mCharacInfo.setCharacter(getContext().guild->getMember(mSelection));
            }
        }
        else if (stdAction == IH::X)
        {
            // si un des personnages en jeu est un allié
            if (std::any_of(mUnitList.begin(), mUnitList.end(), [](UnitList::Pair charac){
                return charac.second->isAlly();
            }))
            {
                mPhase = Main;
                mStep = Waiting;
                mBattlefield.showSpawns(false);
                showCursor(false);
            }
        }
    }
    else if (mStep == CharacterSelect)
    {
        if (stdAction == IH::A)
        {
            Character* charac = getContext().guild->getMember(mSelection);
            assert(charac != nullptr); //on sait jamais
            charac->setBattlefield(mBattlefield);
            charac->addToUnitList(mUnitList);
            charac->addToScene(mScene);
            charac->setCoords(mCursorCoords);
            charac->getEntity()->setAnimationAndFacing(Graphism::Animations::Idle, Direction::Down);
            charac->init();

            //plop
            mStep = FacingSelect;
            initFacingSelectArrows();
            showCursor(false);
        }
        else if (stdAction == IH::Left)
        {
            if (mSelection == 0)
                mSelection = getContext().guild->getMemberCount();
            mSelection--;

            assert(getContext().guild->getMember(mSelection));
            mEntity = *getContext().guild->getMember(mSelection)->getEntity();
            mEntity.setAnimationAndFacing(Graphism::Animations::Idle, Direction::Down);

            mCharacInfo.setCharacter(getContext().guild->getMember(mSelection));
        }
        else if (stdAction == IH::Right)
        {
            mSelection++;
            if (mSelection >= getContext().guild->getMemberCount())
                mSelection = 0;

            assert(getContext().guild->getMember(mSelection));
            mEntity = *getContext().guild->getMember(mSelection)->getEntity();
            mEntity.setAnimationAndFacing(Graphism::Animations::Idle, Direction::Down);

            mCharacInfo.setCharacter(getContext().guild->getMember(mSelection));
        }
        else if (stdAction == IH::B)
        {
            mStep = TileSelect;
            mBattlefield.showSpawns();
            mCharacInfo.setCharacter(nullptr);
        }
    }
    else if (mStep == FacingSelect)
    {
        if (stdAction == IH::Up)
            getContext().guild->getMember(mSelection)->setFacing(Direction::Up);
        else if (stdAction == IH::Down)
            getContext().guild->getMember(mSelection)->setFacing(Direction::Down);
        else if (stdAction == IH::Left)
            getContext().guild->getMember(mSelection)->setFacing(Direction::Left);
        else if (stdAction == IH::Right)
            getContext().guild->getMember(mSelection)->setFacing(Direction::Right);

        else if (stdAction == IH::A)
        {
            mStep = TileSelect;
            showCursor();
            mBattlefield.showSpawns();
        }
        else if (stdAction == IH::B)
        {
            mStep = CharacterSelect;
            getContext().guild->getMember(mSelection)->endBattle();
            showCursor();
        }
    }
}
