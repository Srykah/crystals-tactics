#include "States/Menu/Pause.hpp"
#include "States/Arch/StateStack.hpp"
#include "GUI/Button.hpp"
#include "Other/Utility.hpp"
#include "Sound/MusicPlayer.hpp"
#include "Data/ResourceHolder/ResourceHolder.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/View.hpp>

namespace States
{

Pause::Pause(StateStack* stack, Context context)
: State(stack, context)
, mBackgroundSprite()
, mPausedText("Pause", context.fonts->get(Fonts::Main), 70, Graphism::Text::Shadow)
, mGUIContainer()
{
	sf::Vector2f windowSize(context.window->getSize());

	centerOrigin(mPausedText);
	mPausedText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

	auto returnButton = std::make_shared<GUI::Button>(context, GUI::Button::Menu);
	returnButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 75);
	returnButton->setText("Retour");
	returnButton->setCallback([this] ()
	{
		mStack->close(this);
	});

	auto quitButton = std::make_shared<GUI::Button>(context, GUI::Button::Menu);
	quitButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 125);
	quitButton->setText("Quitter");
	quitButton->setCallback([this] ()
	{
		mStack->clear();
	});

	mGUIContainer.pack(returnButton);
	mGUIContainer.pack(quitButton);

	mContext.music->setPaused(true);
}

Pause::~Pause()
{
	mContext.music->setPaused(false);
}

void Pause::draw()
{
	sf::RenderWindow& window = *mContext.window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mPausedText);
	window.draw(mGUIContainer);
}

bool Pause::update(sf::Time)
{
	return false;
}

bool Pause::handleEvent(const Input::Event& event)
{
	mGUIContainer.handleEvent(event);
	return false;
}

bool Pause::handleSignal(const Signal& signal)
{
    return true;
}

}
