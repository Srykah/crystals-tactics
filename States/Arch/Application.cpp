#include "States/Arch/Application.hpp"
#include "States/Menu/Title.hpp"
#include "Other/Utility.hpp"
#include <iostream>
#include <stdexcept>

namespace States
{

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application()
: mWindow(sf::VideoMode::getFullscreenModes()[0], "Crystals : Tactics", sf::Style::Fullscreen)
, mIsFullscreen(true)
, mListener(&mWindow)
{
	mWindow.setKeyRepeatEnabled(false);
	mWindow.setVerticalSyncEnabled(true);

	mFonts.load(Fonts::Main, 	            "Media/Fonts/Sansation.ttf");
	mFonts.load(Fonts::Title,               "Media/Fonts/gcrank.ttf");

	mTextures.load(Textures::Buttons,		"Media/Textures/Buttons.png");
	mTextures.load(Textures::TextField,         "Media/Textures/TextField.png");

	loadEntities();

    mAbilities.init();
    mStats.loadFromFile("Media/Jobs/Stats.xml");
    mEquipments.loadFromFile("Media/Items/Equipments.xml");
    mWeapons.loadFromFile("Media/Items/Weapons.xml");
    mConsumables.init();

	mStateStack.push(new Title(&mStateStack, getContext()));
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

			processInput(TimePerFrame);
			update(TimePerFrame);

			// Check inside this loop, because stack might be empty before update() call
			if (mStateStack.isEmpty())
				mWindow.close();
		}

		render();
		sf::sleep(TimePerFrame-timeSinceLastUpdate);
	}
}

void Application::processInput(sf::Time dt)
{
    mListener.process(dt);
    Input::Event event;
    while(mListener.getEvent(event))
    {
        if (event.sfEvent.type == sf::Event::Closed)
            mWindow.close();
        else if (event.sfEvent.type == sf::Event::KeyPressed && event.sfEvent.key.code == sf::Keyboard::F11)
            switchFullscreen();

        mStateStack.handleEvent(event);
    }
}

void Application::update(sf::Time dt)
{
	mStateStack.update(dt);
	mStateStack.handleSignal();
}

void Application::render()
{
	mWindow.clear();
	mStateStack.draw();
	mWindow.display();
}

void Application::switchFullscreen()
{
    mIsFullscreen = !mIsFullscreen;
    if (mIsFullscreen)
        mWindow.create(sf::VideoMode::getFullscreenModes()[0], "Crystals : Tactics", sf::Style::Fullscreen);
    else
        mWindow.create(sf::VideoMode::getFullscreenModes()[0], "Crystals : Tactics");
}

Context Application::getContext()
{
    return Context(mWindow, mTextures, mFonts, mMusic, mSounds, mEntities,
                   mStats, mEquipments, mWeapons, mConsumables, mAbilities, mGuild);
}

void Application::loadEntities()
{
    mEntities.load(Entities::CursorBack, "Media/Entities/CursorBack/CursorBack.xml");
	mEntities.load(Entities::CursorFront, "Media/Entities/CursorFront/CursorFront.xml");
	mEntities.load(Entities::Arrow, "Media/Entities/Arrow/Arrow.xml");

    mEntities.load(Entities::Protector, "Media/Entities/Protector/Protector.xml");
    /*
    mEntities.load(Entities::Mechanics, "Media/Entities/Mechanics/Mechanics.xml");
    mEntities.load(Entities::Medic, "Media/Entities/Medic/Medic.xml");
    mEntities.load(Entities::Sniper, "Media/Entities/Sniper/Sniper.xml");
    mEntities.load(Entities::Spy, "Media/Entities/Spy/Spy.xml");
    mEntities.load(Entities::Android, "Media/Entities/Android/Android.xml");
    mEntities.load(Entities::DogRobot, "Media/Entities/DogRobot/DogRobot.xml");
    */
}

}
