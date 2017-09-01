#ifndef RESOURCEIDENTIFIERS_HPP_INCLUDED
#define RESOURCEIDENTIFIERS_HPP_INCLUDED

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "Data/ResourceHolder/ResourceHolder.hpp"
#include "Data/Graphism/EntityData.hpp"
#include "Data/Gameplay/StatsData.hpp"
#include "Gameplay/Character/CharacterStructs.hpp"

namespace Textures
{
	enum ID
	{
		TitleScreen,
		Buttons,
		TextField,
		CTLogo,
		TNTeamLogo,
		Moon,
		Meteorites,
		Ocean,
		Desert,
		Volcano,
		Crystals
	};
}

namespace Fonts
{
	enum ID
	{
		Main,
		Title
	};
}

namespace SoundEffect
{
	enum ID
	{
		ButtonSelect,
		ButtonActivate
	};
}

namespace Music
{
	enum ID
	{
		Epilogue
	};
}

namespace Entities
{
    enum ID
    {
        CursorTile,
        Arrow,
        Protector,
        MechProtector,
        /*
        Mechanics,
        Medic,
        Sniper,
        Spy,
        Android,
        DogRobot,
        */
        Unknown
    };
}

namespace Data
{

typedef ResourceHolder<Textures::ID, sf::Texture>			TextureHolder;
typedef ResourceHolder<Fonts::ID, sf::Font>					FontHolder;
typedef ResourceHolder<SoundEffect::ID, sf::SoundBuffer>	SoundBufferHolder;
typedef ResourceHolder<Entities::ID, Data::EntityData>      EntityHolder;

}

Entities::ID        CharTypeToEntitiesID(CharType type);

#endif // RESOURCEIDENTIFIERS_HPP_INCLUDED
