#ifndef CHARACTER_HPP_INCLUDED
#define CHARACTER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <fstream>
#include <bitset>
#include "Graphism/Entity/Entity.hpp"
#include "Graphism/Scene/EntityNode.hpp"
#include "Gameplay/General/Direction.hpp"
#include "Gameplay/General/Stats.hpp"
#include "Gameplay/General/StatusAilment.hpp"
#include "Gameplay/Abilities/Ability.hpp"
#include "Gameplay/Abilities/AbilityFunctions.hpp"
#include "Gameplay/Character/AI.hpp"
#include "Gameplay/Items/Equipment.hpp"
#include "Gameplay/Items/Weapon.hpp"
#include "Gameplay/Battle/BattleContext.hpp"
#include "XML/pugixml.hpp"
#include "Data/ResourceHolder/ResourceIdentifiers.hpp"
#include "States/Arch/Context.hpp"

class UnitList;
class Guild;
class Battlefield;
class Weapon;

class Character
{
public:
    typedef std::unique_ptr<Character> Ptr;

public: // page 1 : creation
    Character(const pugi::xml_node& savefile, States::Context context);
    ~Character();
    void setType(CharType type);
    void setRole(CharRole role);
    void switchMechForm();
    void setAI(AI::Type type);
    void setAlly(bool flag = true);
    void equip(short id);
    void equipWeapon(short id);
private:
    void load(const pugi::xml_node& node);

public: // page 2 : battle
    void startBattle(BattleContext context, sf::Vector2i coords, Direction::Dir facing);
    void setCoords(sf::Vector2i coords);
    void moveCoords(sf::Vector2i offset);
    void setFacing(Direction::Dir facing);
    void incrementSpeedCounter();
    void newTurn();
    void useAbility(short index, sf::Vector2i to);
    void receiveDamage(Stat amount);
    void receiveHeal(float amount);
    void setStatusAilment(StatusAilment sa);
    void removeStatusAilments();
    //to do : removePositiveStatusAilments, removeNegativeStatusAilments
    void endTurn();
    void endBattle();
    Stats checkLevelUps();

private:
    void reset();
    void removeFromScene();
    void removeFromUnitList();

public: //page 3 : getters
    bool                hasMoved()          const;
    bool                hasAttacked()       const;
    bool                hasUsedItem()       const;
    const std::string&  getName()           const;
    CharType       getType()           const;
    CharRole       getRole()           const;
    bool                isMech()            const;
    Stat                getLevel()          const;
    Stat                getExp()            const;
    Stats               getStats()          const;
    ElemAffinities      getAffinities()     const;
    Stat                getHP()             const;
    bool                isDead()            const;
    Stat                getSpeedCounter()   const;
    bool                isReadyToAct()      const;
    sf::Vector2i        getCoords()         const;
    Direction::Dir      getFacing()         const;
    bool                isAlly()            const;
    BattleContext       getBattleContext()  const;
    short               getUnitListKey()    const;
    AI::Type            getAI()             const;
    bool                isBot()             const;
    CharBuild      getBuild()          const;
    AbilityArray&       getAbilities();
    Graphism::Entity*   getEntity();
    Graphism::Node::Key getSceneKey()       const;
    Graphism::EntityNode* getNode();

private:
    static const short HAS_MOVED = 0;
    static const short HAS_ATTACKED = 1;
    static const short HAS_USED_ITEM = 2;

private:
    std::string         mName;
    CharType       mType;
    CharRole       mRole;
    AI::Type            mAIType;
    bool                mIsAlly;

    Graphism::EntityNode*   mEntityNode;
    sf::CircleShape*        mCircle;
    States::Context         mContext;
    BattleContext           mBattleContext;

    Stat            mLevel;
    Stat            mExperience;
    Stats           mStats;
    CharBuild  mBuild;
    AbilityArray    mAbilities;
    ElemAffinities  mAffinities;

    std::vector<SA> mAilments;
    short           mUnitListKey;
    sf::Vector2i    mCoords;
    std::bitset<3>  mState;
    Stat            mSpeedCounter;
    Stat            mHP;
    bool            mMechForm;
};

#endif // CHARACTER_HPP_INCLUDED
