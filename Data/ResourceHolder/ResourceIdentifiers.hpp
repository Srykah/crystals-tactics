#ifndef RESOURCEIDENTIFIERS_HPP_INCLUDED
#define RESOURCEIDENTIFIERS_HPP_INCLUDED

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "Data/ResourceHolder/ResourceHolder.hpp"
#include "Data/Graphism/EntityData.hpp"
#include "Data/Gameplay/StatsData.hpp"
#include "Gameplay/Character/CharacterStructs.hpp"

namespace Fonts
{
	const short Main = 0;
    const short Title = 1;
}

namespace Data
{

typedef ResourceHolder<Textures::ID, sf::Texture>			TextureHolder;
typedef ResourceHolder<Fonts::ID, sf::Font>					FontHolder;
typedef ResourceHolder<SoundEffect::ID, sf::SoundBuffer>	SoundBufferHolder;
typedef ResourceHolder<Entities::ID, Data::EntityData>      EntityHolder;

}

short   CharTypeToEntityID(CharType type);

#endif // RESOURCEIDENTIFIERS_HPP_INCLUDED
