#include "Label.hpp"
#include "Other/Utility.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

Label::Label(const std::string& text, const Data::FontHolder& fonts)
: mText(text, fonts.get(Fonts::Main), 16, Graphism::Text::Shadow)
{
}

bool Label::isSelectable() const
{
    return false;
}

bool Label::handleEvent(const Input::Event& event)
{
    return true;
}

void Label::update(sf::Time delta)
{

}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mText, states);
}

void Label::setText(const std::string& text)
{
	mText.setString(text);
}

bool Label::contains(sf::Vector2f point) const
{
    return getTransform().transformRect(mText.getGlobalBounds()).contains(point);
}

bool Label::contains(float x, float y) const
{
    return contains(sf::Vector2f(x,y));
}

}
