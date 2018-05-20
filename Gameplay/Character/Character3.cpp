#include "Gameplay/Character/Character.hpp"
#include "Gameplay/Battle/Battlefield.hpp"
#include "Gameplay/Battle/UnitList.hpp"
#include "Gameplay/Items/Weapon.hpp"
#include "Gameplay/Items/Equipment.hpp"
#include "Graphism/Scene/Scene.hpp"

bool Character::hasMoved() const
{
    return mState.test(HAS_MOVED);
}

bool Character::hasAttacked() const
{
    return mState.test(HAS_ATTACKED);
}

bool Character::hasUsedItem() const
{
    return mState.test(HAS_USED_ITEM);
}

const sf::String& Character::getName() const
{
    return mName;
}

CharType Character::getType() const
{
    return mType;
}

bool Character::isMech() const
{
    return (mMechForm
            /* || mType == Robodog
            || mType == Robospider
            || mType == Robotortoise
            || mType == Robobear
            || mType == Robotiger
            || mType == MadAndroid */);
}

Stat Character::getLevel() const
{
    return mLevel;
}

Stat Character::getExp() const
{
    return mExperience;
}

Stats Character::getStats() const
{
    Stats stats(mStats);

    if (mBuild.weapon != nullptr)
        stats += mBuild.weapon->getStats();

    if (mBuild.head != nullptr)
        stats += mBuild.head->getStats();

    if (mBuild.body != nullptr)
        stats += mBuild.body->getStats();

    if (mBuild.legs != nullptr)
        stats += mBuild.legs->getStats();

    if (mBuild.accessory != nullptr)
        stats += mBuild.accessory->getStats();

    return stats;
}

ElemAffinities Character::getAffinities() const
{
    ElemAffinities aff(mAffinities);

    if (mBuild.head != nullptr)
        aff *= mBuild.head->getAffinities();

    if (mBuild.body != nullptr)
        aff *= mBuild.body->getAffinities();

    if (mBuild.legs != nullptr)
        aff *= mBuild.legs->getAffinities();

    if (mBuild.accessory != nullptr)
        aff *= mBuild.accessory->getAffinities();

    return aff;
}

Stat Character::getHP() const
{
    return mHP;
}

bool Character::isDead() const
{
    return getHP() <= 0;
}

Stat Character::getSpeedCounter() const
{
    return mSpeedCounter;
}

bool Character::isReadyToAct() const
{
    return mSpeedCounter >= 100;
}

sf::Vector2i Character::getCoords() const
{
    return mCoords;
}

Direction::Dir Character::getFacing() const
{
    return mEntityNode->entity->getFacing();
}

bool Character::isAlly() const
{
    return mIsAlly;
}

AI::Type Character::getAI() const
{
    return mAIType;
}

bool Character::isBot() const
{
    return getAI() != AI::None;
}

BattleContext Character::getBattleContext() const
{
    return mBattleContext;
}

UnitList::Key Character::getUnitListKey() const
{
    return mUnitListKey;
}

gr::Entity* Character::getEntity()
{
    return mEntityNode->entity.get();
}

gr::EntityNode* Character::getNode()
{
    return mEntityNode;
}

CharBuild Character::getBuild() const
{
    return mBuild;
}

AbilityArray& Character::getAbilities()
{
    return mAbilities;
}
