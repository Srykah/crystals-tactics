#include "../StatesArch/Application.hpp"
#include "../Other/Utility.hpp"
#include "../States/AllStates.hpp"
#include <iostream>

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application()
: mWindow(sf::VideoMode::getFullscreenModes()[0], "Crystals : Tactics")
, mIH()
, mTextures()
, mFonts()
, mMusic()
, mSounds()
, mStatsData(Data::loadStats("Media/Stats/Stats.xml"))
, mItemsData(Data::loadItems("Media/Items/Items.xml"))
, mAbsData(Data::loadAbilities("Media/Abilities/Abilities.xml"))
, mGuild()
, mStateStack(State::Context(mWindow, mIH,
                             mTextures, mFonts, mMusic, mSounds, mEntities,
                             mStatsData, mItemsData, mAbsData,
                             mGuild))
, mIsFullscreen(false)
{
	mWindow.setKeyRepeatEnabled(false);
	mWindow.setVerticalSyncEnabled(true);

	mFonts.load(Fonts::Main, 	            "Media/Fonts/Sansation.ttf");
	mFonts.load(Fonts::Title,               "Media/Fonts/gcrank.ttf");

	mTextures.load(Textures::Buttons,		"Media/Textures/Buttons.png");
	mTextures.load(Textures::TextField,         "Media/Textures/TextField.png");

	mEntities.load(Entities::BattlefieldCursorBack, "Media/Entities/BattlefieldCursorBack/BattlefieldCursorBack.xml");
	mEntities.load(Entities::BattlefieldCursorFront, "Media/Entities/BattlefieldCursorFront/BattlefieldCursorFront.xml");
	mEntities.load(Entities::Arrow, "Media/Entities/Arrow/Arrow.xml");

    mEntities.load(Entities::Tank, "Media/Entities/Tank/Tank.xml");
    mEntities.load(Entities::Mechanics, "Media/Entities/Mechanics/Mechanics.xml");
    mEntities.load(Entities::Medic, "Media/Entities/Medic/Medic.xml");
    mEntities.load(Entities::Gunner, "Media/Entities/Gunner/Gunner.xml");
    mEntities.load(Entities::Murderer, "Media/Entities/Murderer/Murderer.xml");
    mEntities.load(Entities::Android, "Media/Entities/Android/Android.xml");
    mEntities.load(Entities::DogRobot, "Media/Entities/DogRobot/DogRobot.xml");

	registerStates();
	mStateStack.pushState(States::Title);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);

			// Check inside this loop, because stack might be empty before update() call
			if (mStateStack.isEmpty())
				mWindow.close();
		}

		render();
		sf::sleep(TimePerFrame-timeSinceLastUpdate);
	}
}

void Application::processInput()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        mIH.processEvent(event);

        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            mWindow.close();
        else if (event.type == sf::Event::KeyPressed || event.key.code == sf::Keyboard::F11)
        {
            if (mIsFullscreen)
                mWindow.create(sf::VideoMode::getFullscreenModes()[0], "Crystals : Tactics");
            else
                mWindow.create(sf::VideoMode::getFullscreenModes()[0], "Crystals : Tactics", sf::Style::Fullscreen);
        }
    }

    for (IH::SA stdAc = mIH.getStdAction(); stdAc != IH::SA::None; stdAc = mIH.getStdAction())
            mStateStack.handleInput(event, stdAc, mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow)));
}

void Application::update(sf::Time dt)
{
    mIH.update(dt);
	mStateStack.update(dt);
}

void Application::render()
{
	mWindow.clear();
	mStateStack.draw();
	mWindow.display();
}

void Application::registerStates()
{
	mStateStack.registerState<BattleState>(States::Battle);
	mStateStack.registerState<MissionState>(States::Mission);
	mStateStack.registerState<MissionDialogState>(States::MissionDialog);
	mStateStack.registerState<NewGameState>(States::NewGame);
	mStateStack.registerState<PauseState>(States::Pause);
	mStateStack.registerState<SaveMenuState>(States::SaveMenu);
	mStateStack.registerState<SettingsState>(States::Settings);
	mStateStack.registerState<TestState>(States::Test);
	mStateStack.registerState<TitleState>(States::Title);
}
