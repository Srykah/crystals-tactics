#ifndef BATTLEMENU_HPP_INCLUDED
#define BATTLEMENU_HPP_INCLUDED

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <string>
#include "Input/Listener.hpp"

namespace GUI
{

class BattleMenu : public sf::Drawable, public sf::Transformable
{
public:
    struct Entry
    {
        Entry(const sf::String& text, int returnValue, bool grayed = false);

        sf::String text;
        int returnValue;
        bool grayed;
    };

public:
    BattleMenu(const sf::Font& font);
    ~BattleMenu();

    void update(sf::Time delta);
    void handleInput(sf::Event event, Input::StdAction stdAction, sf::Vector2f mousePos);
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;

    void addEntry(const Entry& entry);
    bool hasResult() const;
    int  getResult();

    void clear();

    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;

private:
    const sf::Font& mFont;
    sf::RectangleShape mFrame, mSelection;
    std::vector<Entry> mEntries;
    std::vector<sf::Text> mTexts;
    int mIndexSelection;
    bool mHasResult;
    int mResult;
};


}

#endif // BATTLEMENU_HPP_INCLUDED
