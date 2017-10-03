#ifndef BATTLESTATE_HPP_INCLUDED
#define BATTLESTATE_HPP_INCLUDED

#include "States/Arch/State.hpp"
#include "Graphism/Scene/Scene.hpp"
#include "Graphism/HUD/Cursor.hpp"
#include "Gameplay/Battle/UnitList.hpp"
#include "Gameplay/Battle/Battlefield.hpp"
#include "Gameplay/Battle/BattleContext.hpp"
#include "Gameplay/Story/Guild.hpp"
#include "Gameplay/Cutscene/Cutscene.hpp"
#include <vector>
#include <map>
#include <SFML/Graphics/VertexArray.hpp>

namespace States
{

class Battle : public State
{
public:
    Battle(StateStack* stack, Context context, pugi::xml_node& node);
    ~Battle();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);

private:
    BattleStep          mStep;
    Guild               mEnemyGuild;
    UnitList            mUnitList;
    sf::VertexArray     mBackground;
    Graphism::Scene     mScene;
    Battlefield         mBattlefield;
    Graphism::Cursor    mCursor;
    Cutscene            mCutscene;
    sf::View            mView;

private:
    BattleContext       getBattleContext();
    void                showCursor(bool flag = true);
};

}

#endif // BATTLESTATE_HPP_INCLUDED
