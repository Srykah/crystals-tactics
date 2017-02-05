#include "../Gameplay/Character.hpp"
#include "../Gameplay/Battlefield.hpp"
#include "../Gameplay/UnitList.hpp"
#include "../Gameplay/Weapon.hpp"
#include "../Gameplay/Equipment.hpp"

bool Character::takingTurn() const
{
    return mState.test(TAKING_TURN);
}

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

bool Character::performing() const
{
    return mState.test(MOVING) || mState.test(ATTACKING) || mState.test(USING_ITEM);
}

std::string Character::getName() const
{
    return mName;
}

Character::Type Character::getType() const
{
    return mType;
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

    if (mBuild.helm != nullptr)
        stats += mBuild.helm->getStats();

    if (mBuild.armor != nullptr)
        stats += mBuild.armor->getStats();

    if (mBuild.boots != nullptr)
        stats += mBuild.boots->getStats();

    if (mBuild.accessory != nullptr)
        stats += mBuild.accessory->getStats();

    return stats;
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

bool Character::isAlly() const
{
    return mIsAlly;
}

bool Character::isTarget() const
{
    return mIsTarget;
}

IA::Type Character::getIA() const
{
    return mIA.getType();
}

bool Character::isBot() const
{
    return getIA() != IA::None;
}

Battlefield* Character::getBattlefield() const
{
    return mBattlefield;
}

UnitList* Character::getUnitList() const
{
    return mUnitList;
}

UnitList::Key Character::getUnitListKey() const
{
    return mUnitListKey;
}

Graphism::Entity* Character::getEntity()
{
    return &mEntity;
}

Character::Build Character::getBuild() const
{
    return mBuild;
}

const Ability* Character::getAbility(short index) const
{
    try {
        return &mAbilities.at(index);
    }
    catch(...)
    {
        return nullptr;
    }
}

const std::vector<Ability>& Character::getAllAbilities() const
{
    return mAbilities;
}
