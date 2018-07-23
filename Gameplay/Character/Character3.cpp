#include "Gameplay/Character/Character.hpp"
#include "Gameplay/Battle/Battlefield.hpp"
#include "Gameplay/Battle/UnitList.hpp"
#include "Gameplay/Items/Weapon.hpp"
#include "Gameplay/Items/Equipment.hpp"
#include "Graphism/Scene/Scene.hpp"

Stats Character::getStats() const
{
    return mBattleVars.ailments.alterStats(mBaseStats + mBuild.getStats());
}

bt::BattleContext Character::getBattleContext() const
{
    return mBattleContext;
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
