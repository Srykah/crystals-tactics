#include "../GUI/Button.hpp"
#include "../Other/Utility.hpp"
#include "../Other/ResourceHolder.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

Button::Button(State::Context context, Type type)
: mType(type)
, mCallback()
, mSprite(context.textures->get(Textures::Buttons))
, mText("", context.fonts->get(Fonts::Main), 16)
, mManualDeactivation(false)
, mStayPressed(false)
{
	changeTexture(Normal);

	sf::FloatRect bounds = mSprite.getLocalBounds();
	mText.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

void Button::setCallback(Callback callback)
{
	mCallback = std::move(callback);
}

void Button::setText(const std::string& text)
{
	mText.setString(text);
	centerOrigin(mText);
}

void Button::setManualDeactivation(bool flag)
{
	mManualDeactivation = flag;
}

void Button::stayPressed(bool flag)
{
    mStayPressed = flag;
}

bool Button::isSelectable() const
{
    return true;
}

void Button::select()
{
    if (!isSelected())
    {
        Component::select();
        changeTexture(Selected);
    }
}

void Button::deselect()
{
    if (isSelected())
    {
        Component::deselect();
        changeTexture(Normal);
    }
}

void Button::activate()
{
	Component::activate();

    // If we are toggle then we should show that the button is pressed and thus "toggled".
	if (mManualDeactivation or mStayPressed)
		changeTexture(Pressed);

	if (mCallback)
		mCallback();

    // If we are not a toggle then deactivate the button since we are just momentarily activated.
	if (!mManualDeactivation)
		deactivate();
}

void Button::deactivate()
{
	Component::deactivate();

	if (mManualDeactivation)
        unpress();
}

void Button::unpress()
{
    // Reset texture to right one depending on if we are selected or not.
    if (isSelected())
        changeTexture(Selected);
    else
        changeTexture(Normal);
}


bool Button::handleInput(const sf::Event& event, IH::SA stdAc, sf::Vector2f mousePos)
{
    return true;
}

void Button::update(sf::Time delta)
{

}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
	target.draw(mText, states);
}

void Button::changeTexture(Mode buttonMode)
{
    sf::IntRect textureRect;
	switch(mType)
	{
    case Menu:
        textureRect = sf::IntRect(0, 50*buttonMode, 200, 50);
        break;

    case Settings:
        textureRect = sf::IntRect(200, 50*buttonMode, 50, 50);
        break;

    case UpArrow:
        textureRect = sf::IntRect(250, 50*buttonMode, 50, 50);
        break;

    case DownArrow:
        textureRect = sf::IntRect(300, 50*buttonMode, 50, 50);
        break;

    case LeftArrow:
        textureRect = sf::IntRect(350, 50*buttonMode, 50, 50);
        break;

    case RightArrow:
        textureRect = sf::IntRect(400, 50*buttonMode, 50, 50);
        break;

    case CloseDialog:
        textureRect = sf::IntRect(450, 30*buttonMode, 30, 30);
        break;

    case MoveDialog:
        textureRect = sf::IntRect(480, 30*buttonMode, 30, 30);
        break;

    default:
        break;
	}
	mSprite.setTextureRect(textureRect);
}

bool Button::contains(sf::Vector2f point) const
{
    return getTransform().transformRect(mSprite.getGlobalBounds()).contains(point);
}

bool Button::contains(float x, float y) const
{
    return contains(sf::Vector2f(x,y));
}

}
