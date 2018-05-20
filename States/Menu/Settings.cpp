#include "States/Menu/Settings.hpp"
#include "States/Arch/StateStack.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "Other/Utility.hpp"
#include "Sound/MusicPlayer.hpp"
#include "Sound/SoundPlayer.hpp"

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/View.hpp>

namespace st
{

Settings::Settings(StateStack* stack, Context context) :
    State(stack, context),
    mContainer()
{
    auto musicLabel = std::make_shared<GUI::Label>(ToStr(context.music->getVolume()), *context.fonts);
    musicLabel->setPosition(680, 320);
    mContainer.pack(musicLabel);

    auto lowerMusicButton = std::make_shared<GUI::Button>(context, GUI::Button::LeftArrow);
    lowerMusicButton->setPosition(600, 300);
    lowerMusicButton->setCallback([this, musicLabel] ()
    {
        mContext.music->setVolume(mContext.music->getVolume()-10);
        musicLabel->setText(ToStr(mContext.music->getVolume()));
    });
    lowerMusicButton->setShortcut(sf::Keyboard::Left);
    mContainer.pack(lowerMusicButton);

    auto upperMusicButton = std::make_shared<GUI::Button>(context, GUI::Button::RightArrow);
    upperMusicButton->setPosition(750, 300);
    upperMusicButton->setCallback([this, musicLabel] ()
    {
        mContext.music->setVolume(mContext.music->getVolume()+10);
        musicLabel->setText(ToStr(mContext.music->getVolume()));
    });
    upperMusicButton->setShortcut(sf::Keyboard::Right);
    mContainer.pack(upperMusicButton);



    auto soundsLabel = std::make_shared<GUI::Label>(ToStr(context.sounds->getVolume()), *context.fonts);
    soundsLabel->setPosition(680, 420);
    mContainer.pack(soundsLabel);

    auto lowerSoundsButton = std::make_shared<GUI::Button>(context, GUI::Button::LeftArrow);
    lowerSoundsButton->setPosition(600, 400);
    lowerSoundsButton->setCallback([this, soundsLabel] ()
    {
        mContext.sounds->setVolume(mContext.sounds->getVolume()-10);
        soundsLabel->setText(ToStr(mContext.sounds->getVolume()));
    });
    lowerSoundsButton->setShortcut(sf::Keyboard::Left);
    mContainer.pack(lowerSoundsButton);

    auto upperSoundsButton = std::make_shared<GUI::Button>(context, GUI::Button::RightArrow);
    upperSoundsButton->setPosition(750, 400);
    upperSoundsButton->setCallback([this, soundsLabel] ()
    {
        mContext.sounds->setVolume(mContext.sounds->getVolume()+10);
        soundsLabel->setText(ToStr(mContext.sounds->getVolume()));
    });
    upperSoundsButton->setShortcut(sf::Keyboard::Right);
    mContainer.pack(upperSoundsButton);



    auto returnButton = std::make_shared<GUI::Button>(context, GUI::Button::Menu);
    returnButton->setPosition(600, 500);
    returnButton->setText("Retour");
    returnButton->setCallback([this] ()
    {
        mStack->pop();
    });
    returnButton->setShortcut(sf::Keyboard::Escape);
    mContainer.pack(returnButton);
}

void Settings::draw()
{
    sf::RenderWindow& window = *mContext.window;

    window.setView(window.getDefaultView());

    window.draw(mContainer);
}

bool Settings::update(sf::Time delta)
{
    return false;
}

bool Settings::handleEvent(const Input::Event& event)
{
    mContainer.handleEvent(event);
    return false;
}

bool Settings::handleSignal(const Signal& signal)
{
    return true;
}

}
