#include "../GUI/BattleMenu.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{

BattleMenu::Entry::Entry(const sf::String& text, int returnValue, bool grayed)
: text(text)
, returnValue(returnValue)
, grayed(grayed)
{

}



BattleMenu::BattleMenu(const sf::Font& font)
: mFont(font)
{
    mFrame.setFillColor(sf::Color(0,0,255,204)); //blue 80%
    mFrame.setOutlineColor(sf::Color::White);
    mFrame.setOutlineThickness(5);
    mSelection.setFillColor(sf::Color(128,128,255));
}

BattleMenu::~BattleMenu()
{

}

void BattleMenu::update(sf::Time delta)
{
    //nothing planned for now
}

void BattleMenu::handleInput(sf::Event event, IH::SA stdAction, sf::Vector2f mousePos)
{
    if (stdAction == IH::A && !mEntries[mIndexSelection].grayed)
    {
        mHasResult = true;
        mResult = mEntries[mIndexSelection].returnValue;
    }
    else if (stdAction == IH::Up && mIndexSelection > 0)
    {
        mIndexSelection--;
        mSelection.setPosition(5, 5+40*mIndexSelection);
    }
    else if (stdAction == IH::Down && mIndexSelection < int(mEntries.size())-1)
    {
        mIndexSelection++;
        mSelection.setPosition(5, 5+40*mIndexSelection);
    }
}

void BattleMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mFrame, states);
    target.draw(mSelection, states);
    for (const sf::Drawable& text : mTexts)
        target.draw(text, states);
}

void BattleMenu::addEntry(const Entry& entry)
{
    if (mEntries.empty())
    {
        mIndexSelection = 0;
        mSelection.setPosition(5,5);
        mSelection.setSize(sf::Vector2f(0,40));
    }

    mEntries.push_back(entry);
    mTexts.push_back(sf::Text(entry.text, mFont));

    if (entry.grayed)
        mTexts.back().setFillColor(sf::Color(128,128,128));

    sf::FloatRect rect(mTexts.back().getLocalBounds());
    if (rect.width > mFrame.getSize().x-20)
    {
        mFrame.setSize(sf::Vector2f(rect.width+20, mFrame.getSize().y));
        mSelection.setSize(sf::Vector2f(rect.width+10, 40));
    }

    mTexts.back().setPosition(10,10+40*(mTexts.size()-1));
    mFrame.setSize(sf::Vector2f(mFrame.getSize().x, 10+40*mEntries.size()));
}

bool BattleMenu::hasResult() const
{
    return mHasResult;
}

int BattleMenu::getResult()
{
    mHasResult = false;
    return mResult;
}

void BattleMenu::clear()
{
    mHasResult = false;
    mEntries.clear();
    mTexts.clear();
    mFrame.setSize(sf::Vector2f());
    mSelection.setSize(sf::Vector2f());
}

sf::FloatRect BattleMenu::getLocalBounds() const
{
    return mFrame.getGlobalBounds();
}

sf::FloatRect BattleMenu::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}

}
