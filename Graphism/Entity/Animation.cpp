#include "Graphism/Entity/Animation.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <sstream>
#include <stdexcept>

namespace gr
{

Animation::Animation(const dt::AnimationData& data)
: mAnimData(data)
, mSprite(data.texture)
, mCurrentFrame(0)
, mElapsedTime(sf::Time::Zero)
{
    restart();
}

void Animation::update(sf::Time dt)
{
    if (!isFinished()) //If the animation is finished, no need to update it
    {
        sf::Time timePerFrame(mAnimData.duration / float(mAnimData.getNumFrames()));
        mElapsedTime += dt;

        // While we have a frame to process
        while (!isFinished() && mElapsedTime >= timePerFrame)
        {
            mElapsedTime -= timePerFrame;
            if (mAnimData.repeat) //If the animation repeats and the next frame equals the size, make it the first
                mCurrentFrame = (mCurrentFrame + 1) % mAnimData.getNumFrames();
            else
                mCurrentFrame++; //If the animation doesn't repeat, increment it simply (it will go off the array after mDuration)

            if (!isFinished()) //If the current frame index isn't out of the array, set the texture rect and origin
            {
                mSprite.setTextureRect(mAnimData.frames.at(mCurrentFrame).textureRect);
                mSprite.setOrigin(mAnimData.frames.at(mCurrentFrame).origin);
            }
        }
    }
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void Animation::restart()
{
	mCurrentFrame = 0;
	mElapsedTime = sf::Time::Zero;
	mSprite.setTextureRect(mAnimData.frames.at(0).textureRect);
	mSprite.setOrigin(mAnimData.frames.at(0).origin);
}

sf::Time Animation::getElapsedTime() const
{
    return mElapsedTime;
}

bool Animation::isFinished() const
{
    return mCurrentFrame >= mAnimData.getNumFrames();
}

bool Animation::isRepeating() const
{
	return mAnimData.repeat;
}

sf::Time Animation::getDuration() const
{
	return mAnimData.duration;
}

sf::FloatRect Animation::getLocalBounds() const
{
	return mSprite.getLocalBounds();
}

}
