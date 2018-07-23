#ifndef CHARACTER_HPP_INCLUDED
#define CHARACTER_HPP_INCLUDED

#include "Gameplay/Character/Identity.hpp"
#include "Gameplay/General/Stats.hpp"
#include "Gameplay/Character/BattleVars.hpp"
#include "Gameplay/Character/Build.hpp"
#include "Gameplay/Character/AbilitySet.hpp"
#include "Graphism/Scene/EntityNode.hpp"
#include "XML/pugixml.hpp"
#include "States/Arch/Context.hpp"
#include "Gameplay/Battle/BattleContext.hpp"
#include "Gameplay/General/Direction.hpp"
#include "Gameplay/General/StatusAilment.hpp"

#include <SFML/Graphics/CircleShape.hpp>

class UnitList;
class Guild;
class Battlefield;

namespace ch
{

class Character
{
public:
    typedef std::unique_ptr<Character> Ptr;

public: // page 1 : creation
    Character(const pugi::xml_node& savefile, sa::Context context);
    ~Character();

private:
    void load(const pugi::xml_node& node);

public: // page 2 : battle
    void startBattle(bt::BattleContext context, sf::Vector2i coords, Direction::Dir facing);
    void incrementSpeedCounter();
    bool isReadyToAct() const;
    void newTurn();
    void setCoords(sf::Vector2i coords);
    void moveCoords(sf::Vector2i offset);
    void useAbility(short index, sf::Vector2i to);
    void loseHP(Stat amount);
    void gainHP(Stat amount);
    void endTurn();
    void endBattle();
    Stats checkLevelUps();

private:
    void reset();
    void removeFromScene();
    void removeFromUnitList();

public: //page 3 : getters
    Identity&           getIdentity();
    const Identity&     getIdentity()       const;
    Stats&              getStats();
    const Stats&        getStats()          const;
    BattleVars&         getBattleVars();
    const BattleVars&   getBattleVars()     const;
    CharBuild&          getBuild();
    const CharBuild&    getBuild()          const;
    AbilitySet&         getAbilities();
    const AbilitySet&   getAbilities()      const;
    bt::BattleContext   getBattleContext()  const;
    const gr::Entity*   getEntity()         const;
    gr::Entity*         getEntity();
    //gr::EntityNode*     getNode();

private:
    Identity            mIdentity;
    Stats               mBaseStats;
    BattleVars          mBattleVars;
    StatusAilments      mStatusAilments;
    Build               mBuild;
    AbilitySet          mAbilities;

    gr::EntityNode*     mEntityNode;
    sf::CircleShape*    mCircle;
    sa::Context         mContext;
    bt::BattleContext   mBattleContext;
};

}

#endif // CHARACTER_HPP_INCLUDED
