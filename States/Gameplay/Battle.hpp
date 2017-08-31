#ifndef BATTLESTATE_HPP_INCLUDED
#define BATTLESTATE_HPP_INCLUDED

#include "States/Arch/State.hpp"
#include "Graphism/Scene/Scene.hpp"
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
    Guild               mEnemyGuild;
    UnitList            mUnitList;
    Battlefield         mBattlefield;

    sf::View            mView;
    sf::VertexArray     mBackground;
    Graphism::Scene     mScene;
    Cutscene            mCutscene;

private:
    BattleContext       getBattleContext();
};

}

#endif // BATTLESTATE_HPP_INCLUDED
