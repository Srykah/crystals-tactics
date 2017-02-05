#ifndef BOOK_RESOURCEIDENTIFIERS_HPP
#define BOOK_RESOURCEIDENTIFIERS_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "../Graphism/Entity.hpp"

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
        BattlefieldCursorBack,
        BattlefieldCursorFront,
        Arrow,
        Tank,
        Mechanics,
        Medic,
        Gunner,
        Murderer,
        Android,
        DogRobot,
        Unknown
    };
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>			TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>					FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID>	SoundBufferHolder;
typedef ResourceHolder<Graphism::Entity, Entities::ID>      EntityHolder;

#endif // BOOK_RESOURCEIDENTIFIERS_HPP
