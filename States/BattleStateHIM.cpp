#include "../States/BattleState.hpp"
#include <cassert>
#include <algorithm>

void BattleState::handleInputMain(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos)
{
    if (mStep == Waiting) // yeah, I really don't want to indent everything for a single condition
        return;

    Character* charac = mUnitList.getUnit(mCurUnitKey); // since we're not waiting, we assume it's not nullptr
    assert(charac != nullptr); // (we still check :p)

    int res = -1;
    if (mStep == AbilitySelect || mStep == ActionSelect || mStep == ItemSelect)
    {
        mMenu.handleInput(event, stdAction, mousePos);
        if (mMenu.hasResult())
            res = mMenu.getResult();
    }

    if (mStep == FreeView && stdAction == IH::A) // if we were in free view and we press A, prompt the main menu
    {
        mBattlefield.setCursorCoords(charac->getCoords());
        mBattlefield.showCursor(false);
        mView.setCenter(mBattlefield.getCursorPosition());
        mCharacInfo.setCharacter(mUnitList.getUnitByTile(mBattlefield.getCursorCoords()));
        mStep = ActionSelect;
    }
    else if (mStep == TileSelect)
    {
        if (stdAction == IH::Up
         || stdAction == IH::Down
         || stdAction == IH::Left
         || stdAction == IH::Right) // if we moved the cursor, update the area of effect
        {
            mBattlefield.clearSelection();
            std::vector<sf::Vector2i> range = charac->getAbility(mSelection)->getRange();
            sf::Vector2i cursor = mBattlefield.getCursorCoords();
            if (std::find(range.begin(), range.end(), cursor) != range.end())
                mBattlefield.setZoneSelection(charac->getAbility(mSelection)->getArea(cursor));
        }
        else if (stdAction == IH::A) // if we selected a valid tile, use the ability there (and clear the paint)
        {
            std::vector<sf::Vector2i> range = charac->getAbility(mSelection)->getRange();
            if (std::find(range.begin(), range.end(), mBattlefield.getCursorCoords()) != range.end())
            {
                mBattlefield.clearPaint();
                mBattlefield.showCursor(false);
                charac->useAbility(mSelection, mBattlefield.getCursorCoords());
                mStep = Waiting;
            }
        }
        else if (stdAction == IH::B) // if we press B cancel and return to (appropriate) menu
        {
            mBattlefield.clearPaint();
            mBattlefield.setCursorCoords(charac->getCoords());
            mBattlefield.showCursor(false);
            mView.setCenter(mBattlefield.getCursorPosition());

            if (mSelection == 0)
                mStep = ActionSelect;
            else
                mStep = AbilitySelect;
        }
    }
    else if (mStep == ActionSelect)
    {
        if (stdAction == IH::B) // if we press B while on main menu we become able to move around
        {
            mStep = FreeView;
            mBattlefield.showCursor(true);
        }
        else if (res == 0) // d�placement
        {
            mStep = TileSelect;
            mSelection = 0;
            mBattlefield.setZoneHighlight(charac->getAbility(mSelection)->getRange());
            mBattlefield.showCursor(true);
        }
        else if (res == 1) // action
        {
            mStep = AbilitySelect;
            buildActionMenu();
        }
        else if (res == 2) // fin du tour
        {
            mStep = FacingSelect;
            initFacingSelectArrows();
        }
    }
    else if (mStep == AbilitySelect)
    {
        if (res != -1)
        {
            mStep = TileSelect;
            mSelection = res;
            mBattlefield.setZoneHighlight(charac->getAbility(mSelection)->getRange());
            mBattlefield.setZoneSelection(charac->getAbility(mSelection)->getArea(mBattlefield.getCursorCoords()));
            mBattlefield.showCursor(true);
        }
        else if (stdAction == IH::B) // if we press B while on abilities menu we go back to main menu
        {
            mStep = ActionSelect;
            buildMainMenu();
        }
    }
    else if (mStep == FacingSelect)
    {
        if (stdAction == IH::Up)
        {
            charac->setFacing(Direction::Up);
        }
        else if (stdAction == IH::Down)
        {
            charac->setFacing(Direction::Down);
        }
        else if (stdAction == IH::Left)
        {
            charac->setFacing(Direction::Left);
        }
        else if (stdAction == IH::Right)
        {
            charac->setFacing(Direction::Right);
        }
        else if (stdAction == IH::A)
        {
            charac->endTurn();
            mStep = Waiting;
        }
        else if (stdAction == IH::B) // if we press B while ending turn we go back to main menu
        {
            mStep = ActionSelect;
            buildMainMenu();
        }
    }
}

void BattleState::buildMainMenu()
{
    Character* charac = mUnitList.getUnit(mCurUnitKey);
    if (charac != nullptr)
    {
        mMenu.clear();
        mMenu.addEntry(GUI::BattleMenu::Entry("D�placement", 0, charac->hasMoved()));
        mMenu.addEntry(GUI::BattleMenu::Entry("Action", 1, charac->hasAttacked()));
        mMenu.addEntry(GUI::BattleMenu::Entry("Fin du tour", 2));
    }
}

void BattleState::buildActionMenu()
{
    Character* charac = mUnitList.getUnit(mCurUnitKey);
    if (charac != nullptr)
    {
        mMenu.clear();
        const std::vector<Ability>& ab_tab = charac->getAllAbilities();
        for (uint_fast8_t /* pour le lulz */ i(1u); i < ab_tab.size(); i++)
            mMenu.addEntry(GUI::BattleMenu::Entry(ab_tab[i].getName(), i));
            // je pourrais avoir besoin d'ajouter ab_tab[i].requirementsMet() � la fin
    }
}
