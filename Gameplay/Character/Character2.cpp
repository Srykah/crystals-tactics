#include "Gameplay/Character/Character.hpp"
#include "Gameplay/Battle/Battlefield.hpp"
#include "Gameplay/Battle/UnitList.hpp"
#include "Gameplay/General/Routines.hpp"
#include "Data/DataHolder/DataIdentifiers.hpp"
#include "Graphism/Scene/Scene.hpp"
#include "Graphism/Scene/EntityNode.hpp"
#include "Graphism/Scene/SimpleNode.hpp"
#include "Other/Utility.hpp"

void Character::startBattle(BattleContext context, sf::Vector2i coords, Direction::Dir facing)
{
    reset();

    mBattleContext = context;

    mUnitListKey = mBattleContext.ul->addUnit(this);

    Graphism::Entity* entity = new Graphism::Entity(mContext.entities->get(CharTypeToEntitiesID(mType)), "idle", facing);
    mEntityNode = new Graphism::EntityNode(entity, mCoords.y+1);
    mEntityNode->setPosition(get2DPos(mCoords));
    mBattleContext.scene->addNode(mEntityNode);

    mCircle = new sf::CircleShape;
    Graphism::SimpleNode* circleNode = new Graphism::SimpleNode(mCircle, -0.1f, getSceneKey());
    circleNode->setOrigin(0.5*TILE_DIM, 0.5*TILE_DIM);
    mBattleContext.scene->addNode(circleNode);

    setCoords(coords);
}

void Character::setCoords(sf::Vector2i coords)
{
    if (mBattleContext.bf->contains(coords))
    {
        mCoords = coords;
        getNode()->setPosition(get2DPos(coords));
        getNode()->setZ(mCoords.y+1);
    }
}

void Character::moveCoords(sf::Vector2i offset)
{
    setCoords(getCoords()+offset);
}

void Character::setFacing(Direction::Dir facing)
{
    getEntity()->setFacing(facing);
}

void Character::incrementSpeedCounter()
{
    mSpeedCounter += getStats().speed;
}

void Character::newTurn()
{
    for(int i(0); i < NB_ABILITIES; i++)
    {
        if (mAbilities[i].counter > 0)
            mAbilities[i].counter--;
    }
}

void Character::receiveDamage(Stat amount)
{
    mHP -= amount;
    if (isDead())
        mHP = 0;
}

void Character::receiveHeal(float amount)
{
    mHP += int(getStats().maxHP * amount);
    if (mHP > getStats().maxHP)
        mHP = getStats().maxHP;
}

void Character::setStatusAilment(StatusAilment sa)
{
    mAilments.push_back(sa);
}

void Character::removeStatusAilments()
{
    mAilments.clear();
}

void Character::endTurn()
{
    mSpeedCounter -= 100;

    if (!hasAttacked())
        mSpeedCounter += 20;
    if (!hasMoved())
        mSpeedCounter += 20;

    mState.reset();
}

void Character::endBattle()
{
    reset();
    removeFromScene();
    mBattleContext = BattleContext();
}

Stats Character::checkLevelUps()
{
    Stats bonus;
    while(mExperience >= 100)
    {
        mLevel++;
        mExperience -= 100;
        bonus += mContext.stats->get(int(mType)).getLvUpStats();
    }

    mStats += bonus;
    return bonus;
}

void Character::reset()
{
    mSpeedCounter = 0;
    mHP = getStats().maxHP;
    mState.reset();
    removeStatusAilments();
}

void Character::removeFromScene()
{
    mBattleContext.scene->removeNode(mEntityNode->getKey());
    mEntityNode = nullptr;
    mCircle = nullptr;
}
