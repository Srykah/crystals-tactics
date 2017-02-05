#include "../Graphism/Text.hpp"

namespace Graphism
{

Text::Text(const sf::String& text, const sf::Font& font, int characterSize, int style, sf::Color color)
: mText(text, font, characterSize)
, mShadow(text, font, characterSize)
, mDrawShadow(style & (1 << 4))
{
    mText.setStyle(style & 15);
    mText.setColor(color);
    mShadow.setStyle(style & 15);
    mShadow.setColor(color * sf::Color(128, 128, 128, 128));
}

Text::~Text()
{

}

void Text::setColor(sf::Color color)
{
    mText.setColor(color);
    mShadow.setColor(color * sf::Color(128, 128, 128, 128));
}

void Text::setString(const sf::String& text)
{
    mText.setString(text);
    mShadow.setString(text);
}

sf::FloatRect Text::getLocalBounds() const
{
    return mText.getLocalBounds();
}

sf::FloatRect Text::getGlobalBounds() const
{
    return mText.getGlobalBounds();
}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    if (mDrawShadow)
    {
        auto shadowStates = states;
        target.draw(mShadow, shadowStates.transform.translate(mShadow.getCharacterSize()/10, mShadow.getCharacterSize()/10));
    }

    target.draw(mText, states);
}

}
