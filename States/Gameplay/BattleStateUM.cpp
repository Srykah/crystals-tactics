#include "States/GameplayStates/BattleState.hpp"

void BattleState::updateMain(sf::Time dt)
{
    if (mUnitList.getUnit(mCurUnitKey) != nullptr && mUnitList.getUnit(mCurUnitKey)->takingTurn()) //if someone is playing
    {
        Character* charac = mUnitList.getUnit(mCurUnitKey);
        charac->update(dt);

        if (!charac->isBot() && mStep == Waiting && !charac->performing())
            //si le personnage contrôlé par le joueur a fini son action, on remet le menu,
            //on remet le curseur en place et on affiche les infos, et on vire les unités mortes
            //note : on a actuellement un problème si l'unité en cours se suicide, mais là j'ai la flemme
        {
            removeDeadUnits();
            mStep = ActionSelect;
            mCursorCoords = charac->getCoords();
            mCharacInfo.setCharacter(charac);
            buildMainMenu();
        }
    }
    else
    {
        if (battleWon())
        {
            mPhase = Ending;
            mStep = Waiting;
            mBattleLost = false; // au cas où
            requestStackPush(States::BattleWon);
        }
        else if (battleLost())
        {
            mPhase = Ending;
            mStep = Waiting;
            mBattleLost = true; // au cas où
            requestStackPush(States::GameOver);
        }
        else
        {
            while (mReadyUnitKeys.empty())
            {
                for (auto unit : mUnitList)
                {
                    unit.second->incrementSpeedCounter();
                    if (unit.second->isReadyToAct())
                        mReadyUnitKeys.push_back(unit.second->getUnitListKey());
                }

                std::sort(mReadyUnitKeys.begin(), mReadyUnitKeys.end(), [this](short left, short right){
                    Character* leftChar(mUnitList.getUnit(left));
                    Character* rightChar(mUnitList.getUnit(right));
                    std::vector<int> leftProps, rightProps;
                    leftProps.push_back(leftChar->getSpeedCounter());
                    leftProps.push_back(leftChar->getStats().speed);
                    leftProps.push_back(leftChar->getLevel());
                    leftProps.push_back(leftChar->getExp());
                    leftProps.push_back(leftChar->isAlly());
                    rightProps.push_back(rightChar->getSpeedCounter());
                    rightProps.push_back(rightChar->getStats().speed);
                    rightProps.push_back(rightChar->getLevel());
                    rightProps.push_back(rightChar->getExp());
                    rightProps.push_back(rightChar->isAlly());

                    return std::lexicographical_compare(leftProps.begin(), leftProps.end(),
                                                        rightProps.begin(), rightProps.end());
                });
            }

            mCurUnitKey = mReadyUnitKeys.back();
            mReadyUnitKeys.pop_back();

            Character* charac = mUnitList.getUnit(mCurUnitKey);
            charac->newTurn();
            mCharacInfo.setCharacter(charac);
            mCursorCoords = charac->getCoords();
            if (!charac->isBot())
            {
                buildMainMenu();
                mStep = ActionSelect;
            }
            else
                mStep = Waiting;
        }
    }
}

bool BattleState::battleWon() const
{
    // tant qu'au moins une cible ennemie est en vie, on n'a pas gagné

    return !std::any_of(mUnitList.begin(), mUnitList.end(), [](const UnitList::Pair& pr)
        {
            return pr.second->isTarget() and !pr.second->isAlly() and !pr.second->isDead();
        });
}

bool BattleState::battleLost() const
{
    return mBattleLost;

    /*
    // si un allié cible est mort, on a perdu

    return std::any_of(mUnitList.begin(), mUnitList.end(), [](const UnitList::Pair& pr)
        {
            return pr.second->isAlly() and pr.second->isDead();
        });
    */
}

void BattleState::removeDeadUnits()
{
    for (auto it = mUnitList.begin(); it != mUnitList.end(); it++)
    {
        Character* unit = it->second;

        if (unit->isDead())
        {
            if (unit->isAlly() and unit->isTarget())
                mBattleLost = true;

            unit->endBattle();
            it--;
        }
    }
}
