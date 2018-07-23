#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED

#include "Data/ResourceHolder/ResourceHolder.hpp"
#include "Data/ResourceHolder/ResourceIdentifiers.hpp"
#include "States/Arch/StateStack.hpp"
#include "Sound/MusicPlayer.hpp"
#include "Sound/SoundPlayer.hpp"
#include "Gameplay/Story/Guild.hpp"
#include "Input/Listener.hpp"

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

namespace st
{

class Application
{
public:
    Application();
    void					run();

private:
    void					processInput(sf::Time dt);
    void					update(sf::Time dt);
    void					render();

    void                    switchFullscreen();
    Context                 getContext();

private:
    void                    loadEntities();

    static const sf::Time	TimePerFrame;

    sf::RenderWindow		mWindow;
    bool                    mIsFullscreen;
    Input::Listener         mListener;
    StateStack				mStateStack;

    dt::TextureHolder	    mTextures;
    dt::EntityHolder      mEntities;
    dt::FontHolder		mFonts;
    Sound::MusicPlayer		mMusic;
    Sound::SoundPlayer		mSounds;

    dt::AbilityHolder     mAbilities;
    dt::StatsHolder       mStats;
    dt::EquipmentHolder   mEquipments;
    dt::WeaponHolder      mWeapons;
    dt::ConsumableHolder  mConsumables;

    Guild                   mGuild;
};

}

#endif // APPLICATION_HPP_INCLUDED
