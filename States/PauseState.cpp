#include "../States/PauseState.hpp"
#include "../GUI/Button.hpp"
#include "../Other/Utility.hpp"
#include "../Sound/MusicPlayer.hpp"
#include "../Other/ResourceHolder.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/View.hpp>


PauseState::PauseState(StateStack& stack, State::Context context, const StateData& data)
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
		requestStackClose();
	});

	auto quitButton = std::make_shared<GUI::Button>(context, GUI::Button::Menu);
	quitButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 125);
	quitButton->setText("Quitter");
	quitButton->setCallback([this] ()
	{
		requestStackClear();
	});

	mGUIContainer.pack(returnButton);
	mGUIContainer.pack(quitButton);

	getContext().music->setPaused(true);
}

PauseState::~PauseState()
{
	getContext().music->setPaused(false);
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mPausedText);
	window.draw(mGUIContainer);
}

bool PauseState::update(sf::Time)
{
	return false;
}

bool PauseState::handleInput(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos)
{
	mGUIContainer.handleInput(event, stdAction, mousePos);
	return false;
}

States::ID PauseState::getID() const
{
    return States::Pause;
}
