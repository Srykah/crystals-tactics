#include "Gameplay/Character/Character.hpp"
#include "Gameplay/Battle/Battlefield.hpp"
#include "Gameplay/Story/Guild.hpp"
#include "Gameplay/Battle/UnitList.hpp"
#include "Data/DataHolder/DataIdentifiers.hpp"
#include "Gameplay/General/Routines.hpp"
#include "Gameplay/Abilities/Generic/Movement.hpp"
#include "Gameplay/Abilities/Generic/WeaponAttack.hpp"

Character::Character(const pugi::xml_node& savefile, st::Context context)
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
    mName = node.attribute("name").as_string();
    setType(StrToCharType(node.attribute("type").as_string()));
    mRole = StrToCharRole(node.attribute("role").as_string());
    mAIType = StrToAI(node.attribute("ai").as_string());

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

void Character::setType(CharType type)
{
    mType = type;
    mMechForm = false;
    for (int i(0); i < NB_ABILITIES; i++)
        mAbilities[i] = { -1, 0 };
    // note : pas de sauvegarde de la sélection précédente.
    // à programmer : déséquipement des items indisponibles pour la nouvelle classe.
}

void Character::setRole(CharRole role)
{
    mRole = role;
}

void Character::switchMechForm()
{
    if (mMechForm)
    {
        mMechForm = false;
        if (mEntityNode != nullptr)
        {
            if (mType == CharType::Protector)
                mEntityNode->entity.reset(new gr::Entity(mContext.entities->get(Entities::MechProtector),
                                                               getEntity()->getAnimationName(),
                                                               getEntity()->getFacing()));
        }
    }
    else
    {
        mMechForm = true;
        if (mEntityNode != nullptr)
        {
            if (mType == CharType::Protector)
                mEntityNode->entity.reset(new gr::Entity(mContext.entities->get(Entities::Protector),
                                                               getEntity()->getAnimationName(),
                                                               getEntity()->getFacing()));
            /*
            else if (mType == Sniper)
                mEntity = mContext.entities->get(Entities::Sniper);
            else if (mType == Bomber)
                mEntity = mContext.entities->get(Entities::Bomber);
            else if (mType == Driver)
                mEntity = mContext.entities->get(Entities::Driver);
            */
        }
    }
}

void Character::setAI(AI::Type type)
{
    mAIType = type;
}

void Character::setAlly(bool flag)
{
    mIsAlly = flag;
}

void Character::equip(short id)
{
    Equipment* eqp = & mContext.equipments->get(id);

    switch (eqp->getPosition())
    {
    case Equipment::Head:
        mBuild.head = eqp;
        break;

    case Equipment::Body:
        mBuild.body = eqp;
        break;

    case Equipment::Legs:
        mBuild.legs = eqp;
        break;

    case Equipment::Accessory:
        mBuild.accessory = eqp;

    default:;
    }
}

void Character::equipWeapon(short id)
{
    mBuild.weapon = &mContext.weapons->get(id);
}
