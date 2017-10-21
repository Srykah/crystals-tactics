#include "States/Menu/Title.hpp"
#include "States/Arch/StateStack.hpp"
#include "States/Menu/NewGame.hpp"
#include "States/Menu/SaveMenu.hpp"
#include "States/Editors/EditorsMenu.hpp"
#include "Other/Utility.hpp"
#include "Data/ResourceHolder/ResourceHolder.hpp"
#include "GUI/Button.hpp"
#include "Sound/MusicPlayer.hpp"

#include <SFML/Graphics/RenderTexture.hpp>

const int FADE_IN(0), HOLD(1), FADE_OUT(2), WAITING(3), MENU(4);

namespace States
{

Title::Title(StateStack* stack, Context context)
: State(stack, context)
, mContinueText("Appuyez sur Start / Entrée", context.fonts->get(Fonts::Main), 20, Graphism::Text::Shadow, sf::Color(192,192,192))
, mPhase(FADE_IN)
, mBlinkOn(true)
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
	newButton->setPosition(100, 400);
	newButton->setText("Nouvelle partie");
	newButton->setCallback([this] ()
	{
		mStack->clear();
		mStack->push(new NewGame(mStack, mContext));
		mContext.music->stop();
	});

	auto playButton = std::make_shared<GUI::Button>(context, GUI::Button::Menu);
	playButton->setPosition(100, 450);
	playButton->setText("Continuer");
	playButton->setCallback([this] ()
	{
	    mStack->clear();
		mStack->push(new SaveMenu(mStack, mContext, true));
		mContext.music->stop();
	});

	auto editorsButton = std::make_shared<GUI::Button>(context, GUI::Button::Menu);
	editorsButton->setPosition(100, 500);
	editorsButton->setText("Éditeurs");
	editorsButton->setCallback([this] ()
	{
		mStack->clear();
		mStack->push(new EditorsMenu(mStack, mContext));
		mContext.music->stop();
	});

	auto exitButton = std::make_shared<GUI::Button>(context, GUI::Button::Menu);
	exitButton->setPosition(100, 550);
	exitButton->setText("Quitter le jeu");
	exitButton->setCallback([this] ()
	{
		mStack->clear();
		mContext.music->stop();
	});
	exitButton->setShortcut(sf::Keyboard::Escape);

    mMenu.pack(newButton);
	mMenu.pack(playButton);
	mMenu.pack(editorsButton);
	mMenu.pack(exitButton);
}

void Title::draw()
{
	sf::RenderWindow& window = *mContext.window;

	if(mPhase <= FADE_OUT)
        window.draw(mTNTeamSprite);
    else
	{
	    window.draw(mBackgroundSprite);
        window.draw(mCTSprite);

        if (mPhase == WAITING && mBlinkOn)
            window.draw(mContinueText);
        else if (mPhase == MENU)
            window.draw(mMenu);
	}
}

bool Title::update(sf::Time dt)
{
    mEffectTime += dt;

    if (mPhase == FADE_IN)
    {
        if (mEffectTime < sf::seconds(0.5))
            mTNTeamSprite.setColor(sf::Color(255,255,255,255.f*mEffectTime/sf::seconds(0.5)));
        else
        {
            mTNTeamSprite.setColor(sf::Color::White);
            mEffectTime = sf::Time::Zero;
            mPhase = HOLD;
        }
    }
    else if (mPhase == HOLD)
    {
        if (mEffectTime >= sf::seconds(0.5))
        {
            mEffectTime = sf::Time::Zero;
            mPhase = FADE_OUT;
        }
    }
    else if (mPhase == FADE_OUT)
    {
        if (mEffectTime < sf::seconds(0.5))
            mTNTeamSprite.setColor(sf::Color(255,255,255,255*(1-mEffectTime/sf::seconds(0.5))));
        else
        {
            mTNTeamSprite.setColor(sf::Color::Transparent);
            mEffectTime = sf::Time::Zero;
            mPhase = WAITING;
        }
    }
    else if (mPhase == WAITING)
    {
        if (mEffectTime >= sf::seconds(0.5))
        {
            mBlinkOn = !mBlinkOn;
            mEffectTime = sf::Time::Zero;
        }
    }
    else //if (mPhase == MENU)
        mMenu.update(dt);

	return false;
}

bool Title::handleEvent(const Input::Event& event)
{
    if (mPhase == MENU)
        mMenu.handleEvent(event);

	// If SA::Start event occurs, trigger the next screen / phase
	else if (event.stdAc == Input::Start)
    {
        if (mPhase == FADE_IN || mPhase == HOLD || mPhase == FADE_OUT)
        {
            mEffectTime = sf::Time::Zero;
            mPhase = WAITING;
        }
        else if (mPhase == WAITING)
            mPhase = MENU;
    }


	return false;
}

bool Title::handleSignal(const Signal& signal)
{
    return true;
}

}
