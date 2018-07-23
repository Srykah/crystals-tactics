#ifndef CONTEXT_HPP_INCLUDED
#define CONTEXT_HPP_INCLUDED

#include "Data/DataIdentifiers.hpp"

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

Cette structure gère le contexte d'application dans lequel l'écran est
ouvert.
Il contient, dans l'ordre :
- la fenêtre, pour avoir sa taille ;
- la texture de rendu, pour dessiner l'écran dedans ;
- les textures génériques à l'appli dont pourrait se servir l'écran ;
- les polices d'écriture de l'appli ;
- le lecteur de musique ;
- le lecteur de sons ;
- les entités génériques à l'appli ;
- la guilde de la partie en cours.

//*/

namespace sa
{

struct Context
{
    Context(sf::RenderWindow& window,
            dt::TextureHolder& textures,
            dt::FontHolder& fonts,
            Sound::MusicPlayer& music,
            Sound::SoundPlayer& sounds,
            dt::EntityHolder& entities,
            dt::StatsHolder& stats,
            dt::EquipmentHolder& equipments,
            dt::WeaponHolder& weapons,
            dt::AbilityHolder& consumables,
            dt::AbilityHolder& abilities,
            Guild& guild)
        : window(window)
        , textures(textures)
        , fonts(fonts)
        , music(music)
        , sounds(sounds)
        , entities(entities)
        , stats(stats)
        , equipments(equipments)
        , weapons(weapons)
        , consumables(consumables)
        , abilities(abilities)
        , guild(guild) {}

    sf::RenderWindow&	    window;
    dt::TextureHolder&      textures;
    dt::FontHolder&	        fonts;
    Sound::MusicPlayer&		music;
    Sound::SoundPlayer&	    sounds;
    dt::EntityHolder&       entities;
    dt::StatsHolder&        stats;
    dt::EquipmentHolder&    equipments;
    dt::WeaponHolder&       weapons;
    dt::AbilityHolder&      consumables;
    dt::AbilityHolder&      abilities;
    Guild&                  guild;
};

}

#endif // CONTEXT_HPP_INCLUDED
