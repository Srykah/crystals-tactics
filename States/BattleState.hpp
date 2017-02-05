#ifndef BATTLESTATE_HPP_INCLUDED
#define BATTLESTATE_HPP_INCLUDED

#include "../StatesArch/State.hpp"
#include "../GUI/BattleMenu.hpp"
#include "../Graphism/Text.hpp"
#include "../Graphism/Transition.hpp"
#include "../Graphism/CharacInfo.hpp"
#include "../Gameplay/UnitList.hpp"
#include "../Gameplay/Battlefield.hpp"
#include <vector>

class BattleState : public State
{
public:
    BattleState(StateStack& stack, State::Context context, const StateData& data);
    ~BattleState();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleInput(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos);
    virtual States::ID  getID() const;

private:
    enum Phase
    {
        Beginning,
        UnitPlacing,
        Main,
        Win,
        GameOver,
        Closing
    };

    enum Step
    {
        FreeView,
        TileSelect,
        CharacterSelect,
        ActionSelect,
        AbilitySelect,
        ItemSelect,
        FacingSelect,
        Waiting
    };

private:
    void initFacingSelectArrows();

    //BattleStateUM
    void updateMain(sf::Time dt);
    bool battleWon() const;
    bool battleLost() const;
    void removeDeadUnits();

    //BattleStateHIUP
    void handleInputUnitPlacing(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos);

    //BattleStateHIM
    void handleInputMain(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos);
    void buildMainMenu();
    void buildActionMenu();

private:
    pugi::xml_node          mNode;

    Phase                   mPhase;
    Step                    mStep;

    std::vector<Character::Ptr> mUnits;
    UnitList                mUnitList;
    Battlefield             mBattlefield;
    GUI::BattleMenu         mMenu;
    Graphism::Entity        mLeftArrow, mRightArrow, mUpArrow, mDownArrow;
    Graphism::Text          mWinMessage, mLoseMessage;
    sf::View                mView;

    int            mSelection;
    Graphism::Entity        mEntity;
    Graphism::CharacInfo    mCharacInfo;
    std::vector<UnitList::Key> mReadyUnitKeys;
    UnitList::Key           mCurUnitKey;
    bool                    mBattleLost;
};


#endif // BATTLESTATE_HPP_INCLUDED
