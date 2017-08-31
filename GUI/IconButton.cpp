#include "GUI/IconButton.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace GUI
{

IconButton::IconButton(const sf::Texture& tex, bool selectable)
: mCallback()
, mSprite(tex)
{
    setSelectable(selectable);
}

IconButton::~IconButton()
{

}

void IconButton::setCallback(Callback callback)
{
	mCallback = std::move(callback);
}

bool IconButton::isSelectable() const
{
    return mIsSelectable;
}

void IconButton::setSelectable(bool flag)
{
    if (flag)
        mSprite.setColor(sf::Color::White);
    else
        mSprite.setColor(sf::Color(128,128,128));

    mIsSelectable = flag;
}

void IconButton::select()
{
    if (isSelectable())
    {
        Component::select();
        mSprite.setColor(sf::Color(192, 192, 192));
    }
}

void IconButton::deselect()
{
    Component::deselect();
    mSprite.setColor(sf::Color::White);
}

void IconButton::activate()
{
    if (isSelectable())
    {
        Component::activate();
        mSprite.setColor(sf::Color(64,64,64));

        if (mCallback)
            mCallback();

        deactivate();
    }
}

void IconButton::deactivate()
{
	Component::deactivate();
	mSprite.setColor(sf::Color::White);
}

bool IconButton::handleEvent(const Input::Event& event)
{
}

void IconButton::update(sf::Time delta)
{

}

void IconButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}

bool IconButton::contains(sf::Vector2f point) const
{
    return getTransform().transformRect(mSprite.getGlobalBounds()).contains(point);
}

bool IconButton::contains(float x, float y) const
{
    return contains(sf::Vector2f(x,y));
}

}
