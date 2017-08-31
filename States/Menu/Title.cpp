#include "States/Menu/Title.hpp"
#include "States/Arch/StateStack.hpp"
#include "States/Menu/NewGame.hpp"
#include "States/Menu/SaveMenu.hpp"
#include "Other/Utility.hpp"
#include "Data/ResourceHolder/ResourceHolder.hpp"
#include "GUI/Button.hpp"
#include "Sound/MusicPlayer.hpp"

#include <SFML/Graphics/RenderTexture.hpp>

namespace States
{

Title::Title(StateStack* stack, Context context)
: State(stack, context)
, mContinueText("Appuyez sur Start / Entrée pour continuer", context.fonts->get(Fonts::Main), 20, Graphism::Text::Shadow, sf::Color(192,192,192))
, mPhase(0)
{
    mTextures.load(Textures::TNTeamLogo, "Media/Textures/Logos/TNTeam.png");
    mTNTeamSprite.setTexture(mTextures.get(Textures::TNTeamLogo));
    centerOrigin(mTNTeamSprite);
    mTNTeamSprite.setPosition(683.f, 384.f);
    mTNTeamSprite.setColor(sf::Color::Transparent);

    mTextures.load(Textures::CTLogo, "Media/Textures/Logos/Splash_half.png");
	mCTSprite.setTexture(mTextures.get(Textures::CTLogo));
	centerOrigin(mCTSprite);
	mCTSprite.setPosition(683.f, 250.f);

	mTextures.load(Textures::TitleScreen, "Media/Textures/Backgrounds/TitleScreen.jpg");
	mBackgroundSprite.setTexture(mTextures.get(Textures::TitleScreen));

	centerOrigin(mContinueText);
	mContinueText.setPosition(683.f, 500.f);

	auto newButton = std::make_shared<GUI::Button>(context, GUI::Button::Menu);
	newButton->setPosition(100, 250);
	newButton->setText("Nouvelle partie");
	newButton->setCallback([this] ()
	{
		mStack->clear();
		mStack->push(new NewGame(mStack, mContext));
		mContext.music->stop();
	});

	auto playButton = std::make_shared<GUI::Button>(context, GUI::Button::Menu);
	playButton->setPosition(100, 300);
	playButton->setText("Continuer");
	playButton->setCallback([this] ()
	{
		mStack->push(new SaveMenu(mStack, mContext, true));
		mContext.music->stop();
	});

	auto exitButton = std::make_shared<GUI::Button>(context, GUI::Button::Menu);
	exitButton->setPosition(100, 400);
	exitButton->setText("Quitter le jeu");
	exitButton->setCallback([this] ()
	{
		mStack->clear();
		mContext.music->stop();
	});
	exitButton->setShortcut(sf::Keyboard::Escape);

    mMenu.pack(newButton);
	mMenu.pack(playButton);
	mMenu.pack(exitButton);
}

void Title::draw()
{
	sf::RenderWindow& window = *mContext.window;

	if(mPhase < 3)
        window.draw(mTNTeamSprite);
    else
	{
	    window.draw(mBackgroundSprite);
        window.draw(mCTSprite);

        if (mPhase == 4)
            window.draw(mContinueText);
	}
}

bool Title::update(sf::Time dt)
{
    mEffectTime += dt;

    if (mPhase == 0)
    {
        if (mEffectTime < sf::seconds(0.5))
            mTNTeamSprite.setColor(sf::Color(255,255,255,255.f*mEffectTime/sf::seconds(0.5)));
        else
        {
            mTNTeamSprite.setColor(sf::Color::White);
            mEffectTime = sf::Time::Zero;
            mPhase++;
        }
    }
    else if (mPhase == 1)
    {
        if (mEffectTime >= sf::seconds(0.5))
        {
            mEffectTime = sf::Time::Zero;
            mPhase++;
        }
    }
    else if (mPhase == 2)
    {
        if (mEffectTime < sf::seconds(0.5))
            mTNTeamSprite.setColor(sf::Color(255,255,255,255*(1-mEffectTime/sf::seconds(0.5))));
        else
        {
            mTNTeamSprite.setColor(sf::Color::Transparent);
            mEffectTime = sf::Time::Zero;
            mPhase++;
        }
    }
    else if (mPhase == 3)
    {
        if (mEffectTime >= sf::seconds(0.5))
        {
            mEffectTime = sf::Time::Zero;
            mPhase++;
        }
    }
    else if (mPhase == 4)
    {
        if (mEffectTime >= sf::seconds(0.5))
        {
            mEffectTime = sf::Time::Zero;
            mPhase--;
        }
    }

	return false;
}

bool Title::handleEvent(const Input::Event& event)
{
	// If SA::Start event occurs, trigger the next screen / phase
	if (event.stdAc == Input::Start)
    {
        if (mPhase == 0 || mPhase == 1 || mPhase == 2)
        {
            mEffectTime = sf::Time::Zero;
            mPhase = 3;
        }
        else if (mPhase == 3 || mPhase == 4)
        {
            mStack->clear();
            mStack->push(new NewGame(mStack, mContext));
        }
    }

	return false;
}

bool Title::handleSignal(const Signal& signal)
{
    return true;
}

}
