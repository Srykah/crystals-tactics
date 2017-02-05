#include "../Gameplay/Character.hpp"
#include "../Gameplay/Battlefield.hpp"
#include "../Gameplay/Guild.hpp"
#include "../Gameplay/UnitList.hpp"
#include "../Other/ResourceHolder.hpp"
#include "../Data/JobsData.hpp"
#include "../Gameplay/GameplayUtility.hpp"

Character::Character(const pugi::xml_node& savefile, State::Context context)
: mType(Character::Unknown)
, mIA(this)
, mIsAlly(false)
, mIsTarget(false)
, mGuild(context.guild)
, mContext(context)
, mLevel(0)
, mExperience(0)
, mBattlefield(nullptr)
, mUnitList(nullptr)
, mCurAbility(0)
, mSpeedCounter(0)
{
    load(savefile);
    init();
}

Character::Character(std::string name, Character::Type type, int level, State::Context context, Guild* guild)
: mName(name)
, mType(Character::Unknown)
, mIA(this)
, mIsAlly(true)
, mIsTarget(false)
, mGuild(guild != nullptr ? guild : context.guild)
, mContext(context)
, mLevel(0)
, mExperience(100*level)
, mBattlefield(nullptr)
, mUnitList(nullptr)
, mCurAbility(0)
, mSpeedCounter(0)
{
    setType(type);
    mStats += context.stats->base[type];
    checkLevelUps();
    init();
}

Character::~Character()
{

}

void Character::load(const pugi::xml_node& node)
{
    mName = node.attribute("name").as_string();

    setType(convertStringToType(node.attribute("type").as_string()));

    if (node.attribute("in_clan").as_bool() or node.child("stats"))
        mStats.load(node.child("stats"));
    else
    {
        mStats += mContext.stats->base[mType];
        mExperience = node.attribute("level").as_int()*100;
        checkLevelUps();
    }

    if (node.attribute("in_clan") or node.attribute("ally"))
        mIsAlly = true;

    if (node.attribute("ia"))
        setIA(convertStringToIA(node.attribute("ia").as_string()));

    if (node.attribute("target"))
        mIsTarget = true;

    init();
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mEntity, states);
}

void Character::update(sf::Time delta)
{
    if (mState.test(TAKING_TURN))
    {
        if (isBot())
            mIA.update(delta);
        else if (performing())
        {
            if (mAbilities[mCurAbility].inProgress())
                mAbilities[mCurAbility].update(delta);
            else if (mState.test(MOVING))
            {
                mState.reset(MOVING);
                mState.set(HAS_MOVED);
            }
            else if (mState.test(ATTACKING))
            {
                mState.reset(ATTACKING);
                mState.set(HAS_ATTACKED);
            }
        }
    }

    mEntity.update(delta);
}

void Character::setType(Character::Type type)
{
    mType = type;
    mEntity = mContext.entities->get(convertTypeToEntitiesID(mType));
    //mAbilities.erase(mAbilities.begin()+2, mAbilities.end());
    //mAbilities.insert(mAbilities.end(), global_abilities.at(type).begin(), global_abilities.at(type).end());
}

void Character::setIA(IA::Type type)
{
    mIA.setType(type);
}

void Character::setAlly(bool flag)
{
    mIsAlly = flag;
}

void Character::setTarget(bool flag)
{
    mIsTarget = flag;
}

void Character::equip(Equipment::Position pos, int id)
{
    switch (pos)
    {
    case Equipment::Head:
        mBuild.helm = &mContext.items->helms[id];
        break;

    case Equipment::Body:
        mBuild.armor = &mContext.items->armors[id];
        break;

    case Equipment::Feet:
        mBuild.boots = &mContext.items->boots[id];
        break;

    case Equipment::Accessory:
        mBuild.accessory = &mContext.items->accessories[id];
    }
}

void Character::equipWeapon(int id)
{
    mBuild.weapon = &mContext.items->weapons[id];
}
