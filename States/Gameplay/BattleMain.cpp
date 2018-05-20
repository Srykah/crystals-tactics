#include "States/Gameplay/BattleMain.hpp"
#include "States/Arch/StateStack.hpp"
#include "Gameplay/General/Routines.hpp"
#include "Graphism/Scene/Node.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "Other/Utility.hpp"

#include "States/Menu/Pause.hpp"
#include "States/Gameplay/BattleObjectives.hpp"

namespace st
{

BattleMain::BattleMain(StateStack* stack, Context context, pugi::xml_node& node)
: BattleState(stack, context,
              BattleContext(mStep, mEnemyGuild, mBattlefield, mUnitList, mScene, mCutscene, mView, mCursor))
, mStep(BattleStep::Objectives)
, mBackground(sf::Quads, 4)
, mCursor(mScene, *context.entities)
{
    mBackground[0].color = sf::Color(0,0,255);
    mBackground[1].position = sf::Vector2f(1366,0);
    mBackground[1].color = sf::Color(0,0,255);
    mBackground[2].position = sf::Vector2f(1366,768);
    mBackground[2].color = sf::Color(0,128,255);
    mBackground[3].position = sf::Vector2f(0,768);
    mBackground[3].color = sf::Color(0,128,255);

    mBattlefield.loadFromFile(node.child("battlefield").attribute("path").as_string(),
                              mScene, mContext.entities, mCursor);

    mCursor.setVisible(false);

    // chargement des unités
    for(auto unit : node.child("units").children())
    {
        Character* charac(new Character(unit, mContext));
        mEnemyGuild.addMember(charac);

        sf::Vector2i coords(unit.attribute("spawn_x").as_int(), unit.attribute("spawn_y").as_int());
        Direction::Dir facing(StrToDir(unit.attribute("facing").as_string()));
        charac->startBattle(mBattleContext, coords, facing);
    }

    mScene.sort();

    mStack->push(new BattleObjectives(mStack, mContext, mBattleContext));
}

BattleMain::~BattleMain()
{

}

void BattleMain::draw()
{
    sf::RenderWindow& window(*mContext.window);

    ///draw the bg (note : the view is supposed to be reset to the default one at the end of each state draw)
    window.draw(mBackground);

    ///the scene is drawn with the context view
    window.setView(mView);
    window.draw(mScene);

    ///we reset the view to the default one
    window.setView(window.getDefaultView());
}

bool BattleMain::update(sf::Time dt)
{
    mScene.update(dt);
    mBattlefield.update(dt);

    return true;
}

bool BattleMain::handleEvent(const Input::Event& event)
{
    if (event.stdAc == Input::Start)
        mStack->push(new Pause(mStack, mContext));

    return false;
}

bool BattleMain::handleSignal(const Signal& signal)
{
    return true;
}

}

/*
void Battle::initFacingSelectArrows()
{
    //on redémarre les animations des flèches pour qu'elles soient synchrones
    for (Direction::Dir dir : {Direction::Up, Direction::Down, Direction::Left, Direction::Right})
        mArrows[dir].restart();

    //puis on les ajoute dans la scène au niveau du personnage actif (via une node invisible)
    sf::Vector2f xOffset(1.5*TILE_DIM, 0.f), yOffset(0.f, 1.5*TILE_DIM);

    mScene.addNode(gr::Node(nullptr, 100.f, mUnitList.getUnit(mCurUnitKey)->getSceneKey()));

    gr::Node upArrow(&mArrows[Direction::Up], 0.f, mArrowsKey);
    upArrow.setPosition(-yOffset);
    mScene.addNode(upArrow);

    gr::Node downArrow(&mArrows[Direction::Down], 0.f, mArrowsKey);
    downArrow.setPosition(yOffset);
    mScene.addNode(downArrow);

    gr::Node leftArrow(&mArrows[Direction::Left], 0.f, mArrowsKey);
    leftArrow.setPosition(-xOffset);
    mScene.addNode(leftArrow);

    gr::Node rightArrow(&mArrows[Direction::Right], 0.f, mArrowsKey);
    rightArrow.setPosition(xOffset);
    mScene.addNode(rightArrow);
}
*/
