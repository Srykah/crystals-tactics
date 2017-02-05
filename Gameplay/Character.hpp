#ifndef CHARACTER_HPP_INCLUDED
#define CHARACTER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <fstream>
#include <bitset>
#include "../Graphism/Entity.hpp"
#include "../Gameplay/Stats.hpp"
#include "../Other/ResourceIdentifiers.hpp"
#include "../Other/Direction.hpp"
#include "../Other/pugixml.hpp"
#include "../Gameplay/Ability.hpp"
#include "../Gameplay/IA.hpp"
#include "../StatesArch/State.hpp" //pour State::Context
#include "../Gameplay/Equipment.hpp"

const size_t NB_ABILITIES(4);

class UnitList;
class Guild;
class Battlefield;
class Weapon;

class Character : public sf::Drawable, public sf::Transformable
{
public:
    typedef std::unique_ptr<Character> Ptr;

    enum Type
    {
        Unknown = -1,
        Tank = 0,
        Mechanics,
        Medic,
        Gunner,
        Murderer,
        Android,
        DogRobot
    };

    struct Build
    {
        Weapon* weapon;
        Equipment *helm, *armor, *boots, *accessory;
    };

public: // page 1 : creation
    Character(const pugi::xml_node& savefile, State::Context context);
    Character(std::string name, Type type, int level, State::Context context, Guild* guild = nullptr);
    ~Character();
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;
void update(sf::Time delta);
    void setType(Type type);
    void setIA(IA::Type type);
    void setAlly(bool flag = true);
    void setTarget(bool flag = true);
    void equip(Equipment::Position pos, int id);
    void equipWeapon(int id);
private:
    void load(const pugi::xml_node& node);

public: // page 2 : battle
    void setBattlefield(Battlefield* battlefield);
    void addToUnitList(UnitList* unitList);
    void init();
    void setCoords(sf::Vector2i);
    void setFacing(Direction::Dir facing);
    void incrementSpeedCounter();
    void newTurn();
    void useAbility(short index, sf::Vector2i to);
    void receiveDamage(Stat amount);
    void receiveHeal(Stat amount);
    void endTurn();
    void endBattle();
    bool checkLevelUps();


public: //page 3 : getters
    bool            takingTurn()        const;
    bool            hasMoved()          const;
    bool            hasAttacked()       const;
    bool            hasUsedItem()       const;
    bool            performing()        const;
    std::string     getName()           const;
    Character::Type getType()           const;
    Stat            getLevel()          const;
    Stat            getExp()            const;
    Stats           getStats()          const;
    Stat            getHP()             const;
    bool            isDead()            const;
    Stat            getSpeedCounter()   const;
    bool            isReadyToAct()      const;
    sf::Vector2i    getCoords()         const;
    bool            isAlly()            const;
    bool            isTarget()          const;
    Battlefield*    getBattlefield()    const;
    UnitList*       getUnitList()       const;
    short           getUnitListKey()    const;
    IA::Type        getIA()             const;
    bool            isBot()             const;
    Build           getBuild()          const;
    const Ability*  getAbility(short index) const;
    const std::vector<Ability>& getAllAbilities() const;
    Graphism::Entity*           getEntity();

private:
    static const short TAKING_TURN = 0;
    static const short MOVING = 1;
    static const short HAS_MOVED = 2;
    static const short ATTACKING = 3;
    static const short HAS_ATTACKED = 4;
    static const short USING_ITEM = 5;
    static const short HAS_USED_ITEM = 6;

private:
    std::string         mName;
    Character::Type     mType;
    IA                  mIA;
    bool                mIsAlly;
    bool                mIsTarget;
    Graphism::Entity    mEntity;
    Build               mBuild;
    std::vector<Ability> mAbilities;
    Guild*              mGuild;
    State::Context      mContext;

    Stat            mLevel;
    Stat            mExperience;
    Stats           mStats;
    Battlefield*    mBattlefield;
    UnitList*       mUnitList;
    short           mUnitListKey;
    sf::Vector2i    mCoords;
    std::bitset<7>  mState;
    uint8_t         mCurAbility;
    Stat            mSpeedCounter;
    Stat            mHP;
};

#endif // CHARACTER_HPP_INCLUDED
