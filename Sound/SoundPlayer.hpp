#ifndef SOUNDPLAYER_HPP_INCLUDED
#define SOUNDPLAYER_HPP_INCLUDED

#include "Data/ResourceHolder/ResourceHolder.hpp"
#include "Data/ResourceHolder/ResourceIdentifiers.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include <list>

namespace Sound
{

class SoundPlayer : private sf::NonCopyable
{
	public:
									SoundPlayer();

		void						play(SoundEffect::ID effect);
		void						play(SoundEffect::ID effect, sf::Vector2f position);

		void						removeStoppedSounds();
		void						setListenerPosition(sf::Vector2f position);
		sf::Vector2f				getListenerPosition() const;

		void						setVolume(float volume);
		float                       getVolume() const;


	private:
		Data::SoundBufferHolder	    mSoundBuffers;
		std::list<sf::Sound>		mSounds;
		float						mVolume;
};

}

#endif // SOUNDPLAYER_HPP_INCLUDED
