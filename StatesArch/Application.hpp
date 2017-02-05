#ifndef BOOK_APPLICATION_HPP
#define BOOK_APPLICATION_HPP

#include "../Other/ResourceHolder.hpp"
#include "../Other/ResourceIdentifiers.hpp"
#include "../StatesArch/StateStack.hpp"
#include "../Sound/MusicPlayer.hpp"
#include "../Sound/SoundPlayer.hpp"
#include "../Gameplay/Guild.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

/*

Application : la classe principal du programme. Elle gère les ressources du jeu, dont leur chargement en RAM, et les transmet aux
différents écrans de jeu via son contexte.

à faire (pêle-mêle) :
  - pouvoir changer les options graphiques pendant le jeu
  - gérer la sauvegarde du jeu

*/
class Application
{
	public:
								Application();
		void					run();


	private:
		void					processInput();
		void					update(sf::Time dt);
		void					render();

		void					registerStates();


	private:
		static const sf::Time	TimePerFrame;

		sf::RenderWindow		mWindow;
		InputHandler            mIH;
		TextureHolder			mTextures;
		EntityHolder            mEntities;
	  	FontHolder				mFonts;
		MusicPlayer				mMusic;
		SoundPlayer				mSounds;

		Data::StatsData         mStatsData;
		Data::ItemsData         mItemsData;
		Data::AbsData           mAbsData;

		Guild                   mGuild;

		StateStack				mStateStack;

		bool                    mIsFullscreen;

};

#endif // BOOK_APPLICATION_HPP
