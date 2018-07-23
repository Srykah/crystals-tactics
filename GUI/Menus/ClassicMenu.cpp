#include "GUI/BattleMenu.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <cassert>

namespace GUI
{

BattleMenu::Entry::Entry(const sf::String& text, int returnValue, bool grayed)
: text(text)
, returnValue(returnValue)
, grayed(grayed)
{
    assert(returnValue != -1); // -1 reserved for no value
}



BattleMenu::BattleMenu(const sf::Font& font)
: mFont(font)
, mIndexSelection(-1)
{
    mFrame.setFillColor(sf::Color(0,0,255,204)); //blue 80%
    mFrame.setOutlineColor(sf::Color::White);
    mFrame.setOutlineThickness(5);
}

BattleMenu::~BattleMenu()
{

}

void BattleMenu::update(sf::Time delta)
{
    //nothing planned for now
}

int BattleMenu::handleInput(sf::Event event, Input::StdAction stdAction, sf::Vector2f mousePos)
{
    if (mIndexSelection != -1)
    {
        if (stdAction == Input::A)
            return mEntries[mIndexSelection].returnValue;
        else if (stdAction == Input::Up)
            goUp();
        else if (stdAction == Input::Down)
            goDown();
    }
    return -1;
}

void BattleMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mFrame, states);
    for (const sf::Drawable& text : mTexts)
        target.draw(text, states);
}

void BattleMenu::addEntry(const Entry& entry)
{
    mEntries.push_back(entry);
    mTexts.push_back(sf::Text(entry.text, mFont));

    if (entry.grayed)
        mTexts.back().setFillColor(sf::Color(128,128,128));
    else if (mIndexSelection == -1)
    {
        mIndexSelection = mEntries.size() - 1;
        mTexts.back().setFillColor(sf::Color(255,192,0));
    }
    mTexts.back().setPosition(10, 10 + 40 * (mTexts.size()-1));

    sf::FloatRect rect(mTexts.back().getLocalBounds());
    mFrame.setSize(sf::Vector2f(std::max(mFrame.getSize().x, rect.width + 20), 10 + 40 * mEntries.size()));
}

void BattleMenu::clear()
{
    mIndexSelection = -1;
    mEntries.clear();
    mTexts.clear();
    mFrame.setSize(sf::Vector2f(20, 20));
}

sf::FloatRect BattleMenu::getLocalBounds() const
{
    return mFrame.getLocalBounds();
}

sf::FloatRect BattleMenu::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}

void BattleMenu::goUp()
{
    int newIndex(mIndexSelection - 1);
    for (; newIndex >= 0 && mEntries[newIndex].grayed; newIndex--);

    if (newIndex >= 0 && !mEntries[newIndex].grayed)
    {
        mTexts[mIndexSelection].setFillColor(sf::Color::White);
        mIndexSelection = newIndex;
        mTexts[newIndex].setFillColor(sf::Color(255,192,0));
    }
}

void BattleMenu::goDown()
{
    int newIndex(mIndexSelection + 1);
    for (; newIndex < mEntries.size() && mEntries[newIndex].grayed; newIndex++);

    if (newIndex < mEntries.size() && !mEntries[newIndex].grayed)
    {
        mTexts[mIndexSelection].setFillColor(sf::Color::White);
        mIndexSelection = newIndex;
        mTexts[newIndex].setFillColor(sf::Color(255,192,0));
    }
}

}
