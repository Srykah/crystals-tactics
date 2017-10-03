#include "States/Gameplay/Battle.hpp"
#include "States/Arch/StateStack.hpp"
#include "Gameplay/General/Routines.hpp"
#include "Graphism/Scene/Node.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "Other/Utility.hpp"

#include "States/Menu/Pause.hpp"
#include "States/Gameplay/BattleObjectives.hpp"

namespace States
{

Battle::Battle(StateStack* stack, Context context, pugi::xml_node& node)
: State(stack, context)
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

    // chargement des unités
    for(auto unit : node.child("units").children())
    {
        Character* charac(new Character(unit, mContext));
        mEnemyGuild.addMember(charac);

        sf::Vector2i coords(unit.attribute("spawn_x").as_int(), unit.attribute("spawn_y").as_int());
        Direction::Dir facing(StrToDir(unit.attribute("facing").as_string()));
        charac->startBattle(getBattleContext(), coords, facing);
    }

    mScene.sort();

    mStack->push(new BattleObjectives(mStack, mContext, getBattleContext()));
}

Battle::~Battle()
{

}

void Battle::draw()
{
    ///save the current view, so we can change it and return to it at the end
    sf::RenderWindow& window = *mContext.window;
    sf::View oldView(window.getView());

    ///draw the bg
    window.setView(window.getDefaultView());
    window.draw(mBackground);

    ///the scene is drawn with the context view
    window.setView(mView);
    window.draw(mScene);

    ///return to previous view
    window.setView(oldView);
}

bool Battle::update(sf::Time dt)
{
    mScene.update(dt);
    mBattlefield.update(dt);

    return true;
}

bool Battle::handleEvent(const Input::Event& event)
{
    if (event.stdAc == Input::Start)
        mStack->push(new Pause(mStack, mContext));

    return false;
}

bool Battle::handleSignal(const Signal& signal)
{
    return true;
}

BattleContext Battle::getBattleContext()
{
    return BattleContext(mStep, mEnemyGuild, mBattlefield, mUnitList, mScene, mCutscene, mView, mCursor);
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

    mScene.addNode(Graphism::Node(nullptr, 100.f, mUnitList.getUnit(mCurUnitKey)->getSceneKey()));

    Graphism::Node upArrow(&mArrows[Direction::Up], 0.f, mArrowsKey);
    upArrow.setPosition(-yOffset);
    mScene.addNode(upArrow);

    Graphism::Node downArrow(&mArrows[Direction::Down], 0.f, mArrowsKey);
    downArrow.setPosition(yOffset);
    mScene.addNode(downArrow);

    Graphism::Node leftArrow(&mArrows[Direction::Left], 0.f, mArrowsKey);
    leftArrow.setPosition(-xOffset);
    mScene.addNode(leftArrow);

    Graphism::Node rightArrow(&mArrows[Direction::Right], 0.f, mArrowsKey);
    rightArrow.setPosition(xOffset);
    mScene.addNode(rightArrow);
}
*/
