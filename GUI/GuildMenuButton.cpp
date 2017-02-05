#include "../GUI/GuildMenuButton.hpp"
#include "../Sound/SoundPlayer.hpp"
#include "../Other/ResourceHolder.hpp"
#include "../Other/Utility.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

GuildMenuButton::GuildMenuButton(State::Context context, Type type)
: mCallback()
, mText("", context.fonts->get(Fonts::Main), 40, Graphism::Text::Bold | Graphism::Text::Shadow)
, mSounds(*context.sounds)
{
	mText.setColor(sf::Color::White);
	switch (type)
	{
    case MissionBoard:
        mText.setString("Tableau des missions");
        mBounds = sf::FloatRect(350,0,650,200);
        break;

    case Shop:
        mText.setString("Boutique");
        mBounds = sf::FloatRect(0,100,300,600);
        break;

    case Clan:
        mText.setString("Clan");
        mBounds = sf::FloatRect(350,450,600,318);
        break;

    case Exit:
        mText.setString("Quitter");
        mBounds = sf::FloatRect(1050,150,316,500);
        break;

    default:
        break;
	}

	centerOrigin(mText);

	mText.setPosition(mBounds.left+mBounds.width/2, mBounds.top+mBounds.height/2);
}

GuildMenuButton::~GuildMenuButton()
{

}

void GuildMenuButton::setCallback(Callback callback)
{
	mCallback = std::move(callback);
}

bool GuildMenuButton::isSelectable() const
{
    return true;
}

void GuildMenuButton::select()
{
    if (!isSelected())
    {
        Component::select();
        mText.setColor(sf::Color::Yellow);
        mSounds.play(SoundEffect::ButtonSelect);
    }
}

void GuildMenuButton::deselect()
{
    if (isSelected())
    {
        Component::deselect();
        mText.setColor(sf::Color::White);
    }
}

void GuildMenuButton::activate()
{
	Component::activate();

	if (mCallback)
        mCallback();

	mSounds.play(SoundEffect::ButtonActivate);

    deactivate();
}

void GuildMenuButton::deactivate()
{
	Component::deactivate();
}

bool GuildMenuButton::handleInput(const sf::Event&, InputHandler::StandardAction, sf::Vector2f)
{
    return true;
}

void GuildMenuButton::update(sf::Time delta)
{

}

void GuildMenuButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mText, states);
}

bool GuildMenuButton::contains(sf::Vector2f point) const
{
    return getTransform().transformRect(mBounds).contains(point);
}

bool GuildMenuButton::contains(float x, float y) const
{
    return contains(sf::Vector2f(x,y));
}

}
