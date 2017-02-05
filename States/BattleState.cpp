#include "../States/BattleState.hpp"
#include "../GUI/Button.hpp"
#include "../GUI/Label.hpp"
#include "../Other/Utility.hpp"

BattleState::BattleState(StateStack& stack, State::Context context, const StateData& data)
: State(stack, context)
, mNode(data.node())
, mPhase(Beginning)
, mStep(Waiting)
, mBattlefield(context.entities, &mUnitList)
, mMenu(context.fonts->get(Fonts::Main))
, mLeftArrow(context.entities->get(Entities::Arrow))
, mRightArrow(context.entities->get(Entities::Arrow))
, mUpArrow(context.entities->get(Entities::Arrow))
, mDownArrow(context.entities->get(Entities::Arrow))
, mWinMessage("Vous avez gagné !", context.fonts->get(Fonts::Main), 70, Graphism::Text::Shadow, sf::Color::Red)
, mLoseMessage("Vous avez perdu...", context.fonts->get(Fonts::Main), 70, Graphism::Text::Shadow, sf::Color::Blue)
, mView(sf::Vector2f(0,0), sf::Vector2f(1366,768))
, mCharacInfo(context)
, mCurUnitKey(0)
, mBattleLost(false)
{
    centerOrigin(mWinMessage);
    centerOrigin(mLoseMessage);
    mWinMessage.setPosition(683, 384);
    mLoseMessage.setPosition(683, 384);

    mCharacInfo.setPosition(0, 618);
    mMenu.setPosition(50,200);

    mLeftArrow.setAnimationAndFacing(Graphism::Animations::Idle, Direction::Left);
    mRightArrow.setAnimationAndFacing(Graphism::Animations::Idle, Direction::Right);
    mUpArrow.setAnimationAndFacing(Graphism::Animations::Idle, Direction::Up);
    mDownArrow.setAnimationAndFacing(Graphism::Animations::Idle, Direction::Down);

    mBattlefield.loadFromFile(mNode.child("battlefield").attribute("path").as_string());
    mView.setCenter(mBattlefield.getCursorPosition());

    // chargement des unités
    for(auto unit : mNode.child("units").children())
    {
        mUnits.emplace_back(new Character(unit, getContext()));

        // order is important : you have to load before calling setAnimationAndFacing on the unit's entity
        // also, setCoords have to be called after setBattlefield since it checks if the coords are not out of bounds
        mUnits.back()->getEntity()->setAnimationAndFacing(Graphism::Animations::Idle, stringToDir(unit.attribute("facing").as_string()));
        mUnits.back()->setBattlefield(&mBattlefield);
        mUnits.back()->addToUnitList(&mUnitList);
        sf::Vector2i coords(unit.attribute("spawn_x").as_int(), unit.attribute("spawn_y").as_int());
        mUnits.back()->setCoords(coords);
        mUnits.back()->setPosition(float(TILE_DIM)*sf::Vector2f(coords.x+0.5, coords.y+0.5));
        mUnits.back()->init();
    }
}

BattleState::~BattleState()
{

}

void BattleState::draw()
{
    ///save the current view, so we can change it and return to it at the end
    sf::RenderWindow& window = *getContext().window;
    sf::View oldView(window.getView());

    ///things that must be drawn with the view centered on the cursor
    window.setView(mView);

    //the battlefield
    window.draw(mBattlefield);

    //the character selected
    if (mStep == CharacterSelect)
        window.draw(mEntity);

    //the arrows around the character during facing selection
    else if (mStep == FacingSelect)
    {
        window.draw(mLeftArrow);
        window.draw(mRightArrow);
        window.draw(mUpArrow);
        window.draw(mDownArrow);
    }

    ///things that must be drawn with the standard view (the default one on a 1366*768 window)
    window.setView(sf::View(sf::FloatRect(0,0,1366,768)));

    //the character information box
    if (mPhase == UnitPlacing || mPhase == Main)
        window.draw(mCharacInfo);

    //the battle menu
    if (mPhase == Main && (mStep == ActionSelect || mStep == AbilitySelect || mStep == ItemSelect))
        window.draw(mMenu);

    //the arrows at the border of the screen during character selection
    else if (mStep == CharacterSelect)
    {
        window.draw(mLeftArrow);
        window.draw(mRightArrow);
    }

    //win or lose messages
    else if (mPhase == Win)
        window.draw(mWinMessage);
    else if (mPhase == GameOver)
        window.draw(mLoseMessage);

    ///return to previous view
    window.setView(oldView);
}

bool BattleState::update(sf::Time dt)
{
    mUnitList.update(dt);
    mBattlefield.update(dt);

    if (mStep == CharacterSelect)
    {
        mEntity.update(dt);
        mLeftArrow.update(dt);
        mRightArrow.update(dt);
    }
    else if (mStep == FacingSelect)
    {
        mUpArrow.update(dt);
        mDownArrow.update(dt);
        mLeftArrow.update(dt);
        mRightArrow.update(dt);
    }

    if (mPhase == Beginning)
    {
        mPhase = UnitPlacing;
        mStep = TileSelect;
        mBattlefield.showCursor();
        mBattlefield.showSpawns();
    }
    else if (mPhase == Main)
        updateMain(dt);

    return true;
}

bool BattleState::handleInput(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos)
{
    if (mStep == TileSelect || mStep == FreeView)
    {
        mBattlefield.handleInput(event, stdAction, mousePos);

        if (stdAction == IH::Up
         || stdAction == IH::Down
         || stdAction == IH::Left
         || stdAction == IH::Right)
        {
            mView.setCenter(mBattlefield.getCursorPosition());
            mCharacInfo.setCharacter(mUnitList.getUnitByTile(mBattlefield.getCursorCoords()));
        }
    }

    if (mPhase == UnitPlacing)
        handleInputUnitPlacing(event, stdAction, mousePos);

    else if (mPhase == Main)
        handleInputMain(event, stdAction, mousePos);

    else if (mPhase == Win && stdAction == IH::A)
    {
        setData(true);
        requestStackClose();
    }
    else if (mPhase == GameOver && stdAction == IH::A)
    {
        setData(false);
        requestStackClose();
    }

    if (stdAction == IH::Start)
        requestStackPush(States::Pause);

    return false;
}

States::ID BattleState::getID() const
{
    return States::Battle;
}

void BattleState::initFacingSelectArrows()
{
    //on redémarre les animations des flèches pour qu'elles soient synchrones
    mLeftArrow.restart();
    mRightArrow.restart();
    mUpArrow.restart();
    mDownArrow.restart();

    //puis on les place au niveau du curseur
    sf::Vector2f v(mBattlefield.getCursorPosition());
    mLeftArrow.setPosition(v.x-50, v.y);
    mRightArrow.setPosition(v.x+50, v.y);
    mUpArrow.setPosition(v.x, v.y-50);
    mDownArrow.setPosition(v.x, v.y+50);
}
