#include "../Sound/MusicPlayer.hpp"


MusicPlayer::MusicPlayer()
: mMusic()
, mFilenames()
, mVolume(100.f)
{
	mFilenames[Music::Epilogue]    = "Media/Music/Epilogue.ogg";
}

void MusicPlayer::play(Music::ID theme)
{
	std::string filename = mFilenames[theme];

	if (!mMusic.openFromFile(filename))
		throw std::runtime_error("Music " + filename + " could not be loaded.");

	mMusic.setVolume(mVolume);
	mMusic.setLoop(true);
	mMusic.play();
}

void MusicPlayer::stop()
{
	mMusic.stop();
}

void MusicPlayer::setVolume(float volume)
{
	if (0 <= volume && volume <= 100) mVolume = volume;
}

float MusicPlayer::getVolume() const
{
    return mVolume;
}

void MusicPlayer::setPaused(bool paused)
{
	if (paused)
		mMusic.pause();
	else
		mMusic.play();
}
