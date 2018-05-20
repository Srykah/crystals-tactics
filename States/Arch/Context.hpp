#ifndef CONTEXT_HPP_INCLUDED
#define CONTEXT_HPP_INCLUDED

#include "Data/ResourceHolder/ResourceIdentifiers.hpp"
#include "Data/DataHolder/DataIdentifiers.hpp"
#include "Data/Gameplay/AbilityHolder.hpp"
#include "Data/Gameplay/ConsumableHolder.hpp"

namespace sf
{
    class RenderWindow;
}

namespace Sound
{
    class MusicPlayer;
    class SoundPlayer;
}

class Guild;

/*//

Context

Cette structure g�re le contexte d'application dans lequel l'�cran est
ouvert.
Il contient, dans l'ordre :
- la fen�tre, pour avoir sa taille ;
- la texture de rendu, pour dessiner l'�cran dedans ;
- les textures g�n�riques � l'appli dont pourrait se servir l'�cran ;
- les polices d'�criture de l'appli ;
- le lecteur de musique ;
- le lecteur de sons ;
- les entit�s g�n�riques � l'appli ;
- la guilde de la partie en cours.

//*/

namespace st
{

struct Context
{
    Context(sf::RenderWindow& window,
            Data::TextureHolder& textures,
            Data::FontHolder& fonts,
            Sound::MusicPlayer& music,
            Sound::SoundPlayer& sounds,
            Data::EntityHolder& entities,
            Data::StatsHolder& stats,
            Data::EquipmentHolder& equipments,
            Data::WeaponHolder& weapons,
            Data::ConsumableHolder& consumables,
            Data::AbilityHolder& abilities,
            Guild& guild);

    sf::RenderWindow*	    window;
    Data::TextureHolder*    textures;
    Data::FontHolder*	    fonts;
    Sound::MusicPlayer*		music;
    Sound::SoundPlayer*	    sounds;
    Data::EntityHolder*     entities;
    Data::StatsHolder*      stats;
    Data::EquipmentHolder*  equipments;
    Data::WeaponHolder*     weapons;
    Data::ConsumableHolder* consumables;
    Data::AbilityHolder*    abilities;
    Guild*                  guild;
};

}

#endif // CONTEXT_HPP_INCLUDED
