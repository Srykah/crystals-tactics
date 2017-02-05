#include "../States/SettingsState.hpp"
#include "../GUI/Button.hpp"
#include "../GUI/Label.hpp"
#include "../Other/Utility.hpp"
#include "../Sound/MusicPlayer.hpp"
#include "../Sound/SoundPlayer.hpp"

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/View.hpp>


SettingsState::SettingsState(StateStack& stack, State::Context context, const StateData& data) :
    State(stack, context),
    mContainer()
{
    auto musicLabel = std::make_shared<GUI::Label>(toString(context.music->getVolume()), *context.fonts);
    musicLabel->setPosition(680, 320);
    mContainer.pack(musicLabel);

    auto lowerMusicButton = std::make_shared<GUI::Button>(context, GUI::Button::LeftArrow);
    lowerMusicButton->setPosition(600, 300);
    lowerMusicButton->setCallback([this, musicLabel] ()
    {
        getContext().music->setVolume(getContext().music->getVolume()-10);
        musicLabel->setText(toString(getContext().music->getVolume()));
    });
    lowerMusicButton->setShortcut(sf::Keyboard::Left);
    mContainer.pack(lowerMusicButton);

    auto upperMusicButton = std::make_shared<GUI::Button>(context, GUI::Button::RightArrow);
    upperMusicButton->setPosition(750, 300);
    upperMusicButton->setCallback([this, musicLabel] ()
    {
        getContext().music->setVolume(getContext().music->getVolume()+10);
        musicLabel->setText(toString(getContext().music->getVolume()));
    });
    upperMusicButton->setShortcut(sf::Keyboard::Right);
    mContainer.pack(upperMusicButton);



    auto soundsLabel = std::make_shared<GUI::Label>(toString(context.sounds->getVolume()), *context.fonts);
    soundsLabel->setPosition(680, 420);
    mContainer.pack(soundsLabel);

    auto lowerSoundsButton = std::make_shared<GUI::Button>(context, GUI::Button::LeftArrow);
    lowerSoundsButton->setPosition(600, 400);
    lowerSoundsButton->setCallback([this, soundsLabel] ()
    {
        getContext().sounds->setVolume(getContext().sounds->getVolume()-10);
        soundsLabel->setText(toString(getContext().sounds->getVolume()));
    });
    lowerSoundsButton->setShortcut(sf::Keyboard::Left);
    mContainer.pack(lowerSoundsButton);

    auto upperSoundsButton = std::make_shared<GUI::Button>(context, GUI::Button::RightArrow);
    upperSoundsButton->setPosition(750, 400);
    upperSoundsButton->setCallback([this, soundsLabel] ()
    {
        getContext().sounds->setVolume(getContext().sounds->getVolume()+10);
        soundsLabel->setText(toString(getContext().sounds->getVolume()));
    });
    upperSoundsButton->setShortcut(sf::Keyboard::Right);
    mContainer.pack(upperSoundsButton);



    auto returnButton = std::make_shared<GUI::Button>(context, GUI::Button::Menu);
    returnButton->setPosition(600, 500);
    returnButton->setText("Retour");
    returnButton->setCallback([this] ()
    {
        requestStackPop();
    });
    returnButton->setShortcut(sf::Keyboard::Escape);
    mContainer.pack(returnButton);
}

void SettingsState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

    window.draw(mContainer);
}

bool SettingsState::update(sf::Time delta)
{
    return false;
}

bool SettingsState::handleInput(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos)
{
    mContainer.handleInput(event, stdAction, mousePos);
    return false;
}

States::ID SettingsState::getID() const
{
    return States::Settings;
}

