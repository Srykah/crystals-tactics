#ifndef TEXT_HPP_INCLUDED
#define TEXT_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>

namespace Graphism
{

class Text : public sf::Drawable, public sf::Transformable
{
public:
    enum Style
    {
        Regular = 0,
        Bold = 1 << 0,
        Italic = 1 << 1,
        Underlined = 1 << 2,
        StrikeThrough = 1 << 3,
        Shadow = 1 << 4
    };

                    Text(const sf::String& text,
                         const sf::Font& font,
                         int characterSize = 30,
                         int style = Style::Regular,
                         sf::Color color = sf::Color::White);
                    ~Text();

    void            setColor(sf::Color color);
    void            setString(const sf::String& text);

    sf::FloatRect   getLocalBounds() const;
    sf::FloatRect   getGlobalBounds() const;

    virtual void    draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;

private:
    sf::Text        mText;
    sf::Text        mShadow;
    bool            mDrawShadow;
};

}

#endif // TEXT_HPP_INCLUDED
