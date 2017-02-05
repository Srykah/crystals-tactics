#include "../Gameplay/Character.hpp"
#include "../Gameplay/Battlefield.hpp"
#include "../Gameplay/UnitList.hpp"
#include "../Data/JobsData.hpp"

void Character::setBattlefield(Battlefield* battlefield)
{
    mBattlefield = battlefield;
}

void Character::addToUnitList(UnitList* unitList)
{
    if(mUnitList != unitList)
    {
        mUnitList = unitList;
        mUnitListKey = mUnitList->addUnit(this);
    }
}

void Character::init()
{
    mSpeedCounter = 0;
    mHP = getStats().maxHP;
    mState.reset();
}

void Character::setCoords(sf::Vector2i coords)
{
    if (mBattlefield != nullptr && coords.x >= 0 && coords.y >= 0 && coords.x < mBattlefield->getGridSize().x && coords.y < mBattlefield->getGridSize().y)
    {
        mCoords = coords;
        if (mUnitList != nullptr)
            mUnitList->sortUnits();
    }
}

void Character::setFacing(Direction::Dir facing)
{
    mEntity.setFacing(facing);
}

void Character::incrementSpeedCounter()
{
    mSpeedCounter += getStats().speed;
}

void Character::newTurn()
{
    mState.set(TAKING_TURN);
    mIA.newTurn();
}


void Character::useAbility(short index, sf::Vector2i to)
{
    if (index == 0)
        mState.set(MOVING);
    else
        mState.set(ATTACKING);
    // note : je n'ai pas pris en compte le cas où on utilise un objet (je mettrai sûrement cette capacité en troisième)
    mAbilities[index].use(to);
    mCurAbility = index;
}

void Character::receiveDamage(Stat amount)
{
    mHP -= amount;
    if (isDead())
        mHP = 0;
}

void Character::receiveHeal(Stat amount)
{
    mHP += amount;
    if (mHP > getStats().maxHP)
        mHP = getStats().maxHP;
}

void Character::endTurn()
{
    mSpeedCounter = 0;

    if (!hasAttacked())
        mSpeedCounter += 20;
    if (!hasMoved())
        mSpeedCounter += 20;

    mState.reset();
}

void Character::endBattle()
{
    mBattlefield = nullptr;
    mUnitList->removeUnit(mUnitListKey);
    mUnitList = nullptr;
    mUnitListKey = -1;

    init();
}

bool Character::checkLevelUps()
{
    bool hasLeveledUp(false);

    while(mExperience >= 100)
    {
        hasLeveledUp = true;
        mLevel++;
        mExperience -= 100;
        mStats += mContext.stats->levelUp[mType];
    }

    return hasLeveledUp;
}
