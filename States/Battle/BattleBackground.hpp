#ifndef BATTLEMAIN_HPP_INCLUDED
#define BATTLEMAIN_HPP_INCLUDED

#include "States/Gameplay/BattleState.hpp"
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

namespace st //TODO : change to bs
{

class BattleBackground : public BattleState
{
public:
    BattleBackground(StateStack* stack, Context context, pugi::xml_node& node);
    ~BattleBackground();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);

private:
    enum Step
    {
        Objectives,
        Loop
    };

    st::State*          mChildState;
    Step                mStep;
    Guild               mEnemyGuild;
    UnitList            mUnitList;
    sf::VertexArray     mBackground;
    gr::Scene           mScene;
    Battlefield         mBattlefield;
    gr::Cursor          mCursor;
    Cutscene            mCutscene;
    sf::View            mView;

private:
    void                showCursor(bool flag = true);
};

}

#endif // BATTLEMAIN_HPP_INCLUDED
