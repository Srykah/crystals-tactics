#include "Gameplay/Character/Character.hpp"
#include "Gameplay/Battle/Battlefield.hpp"
#include "Gameplay/Story/Guild.hpp"
#include "Gameplay/Battle/UnitList.hpp"
#include "Data/DataIdentifiers.hpp"
#include "Gameplay/General/Routines.hpp"
#include "Gameplay/Abilities/Generic/Movement.hpp"
#include "Gameplay/Abilities/Generic/WeaponAttack.hpp"

Character::Character(const pugi::xml_node& savefile, sa::Context context)
: mType(CharType::Unknown)
, mRole(CharRole::None)
, mAIType(AI::None)
, mIsAlly(false)
, mContext(context)
, mSpeedCounter(0)
, mMechForm(false)
{
    load(savefile);
    reset();
}

Character::~Character()
{

}

void Character::load(const pugi::xml_node& node)
{
    mIdentity.load(node.child("identity"));

    mLevel = node.attribute("level").as_int();
    mExperience = node.attribute("experience").as_int();

    if (node.child("stats"))
        mStats.load(node.child("stats"));
    else
    {
        mStats = mContext.stats->get(short(mType)).getBase();
        checkLevelUps();
    }

    int i(0);
    for (auto attr : node.child("abilities").attributes())
    {
        mAbilities[i].id = attr.as_int();
        i++;
    }
}
