#include "../Graphism/Animation.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <sstream>
#include <stdexcept>

Graphism::Animations::Type stringToAT(std::string str)
{
    if (str == "idle") return Graphism::Animations::Idle;
    else if (str == "moving") return Graphism::Animations::Moving;
    else if (str == "bareFistAttack") return Graphism::Animations::BareFistAttack;
    else if (str == "meleeAttack") return Graphism::Animations::MeleeAttack;
    else if (str == "rangeAttack") return Graphism::Animations::RangeAttack;

    std::stringstream error;
    error << "String " << str << " couldn't be converted into Animations::Type";
    throw std::runtime_error(error.str());
}

namespace Graphism
{

Animation::Animation()
: mSprite()
, mCurrentFrame(0)
, mDuration(sf::Time::Zero)
, mElapsedTime(sf::Time::Zero)
, mRepeat(false)
{
}

Animation::Animation(const sf::Texture* texture)
: mSprite(*texture)
, mCurrentFrame(0)
, mDuration(sf::Time::Zero)
, mElapsedTime(sf::Time::Zero)
, mRepeat(false)
{

}

void Animation::setTexture(const sf::Texture* texture)
{
	mSprite.setTexture(*texture);
}

const sf::Texture* Animation::getTexture() const
{
	return mSprite.getTexture();
}

void Animation::addFrame(Frame frame)
{
    mFrames.push_back(frame);
}

std::size_t Animation::getNumFrames() const
{
	return mFrames.size();
}

void Animation::setDuration(sf::Time duration)
{
	mDuration = duration;
}

sf::Time Animation::getDuration() const
{
	return mDuration;
}

void Animation::setRepeating(bool flag)
{
	mRepeat = flag;
}

bool Animation::isRepeating() const
{
	return mRepeat;
}

void Animation::restart()
{
	mCurrentFrame = 0;
	mElapsedTime = sf::Time::Zero;
	mSprite.setTextureRect(mFrames.at(0).textureRect);
	mSprite.setOrigin(mFrames.at(0).origin);
}

bool Animation::isFinished() const
{
    return mCurrentFrame >= mFrames.size();
}

sf::FloatRect Animation::getLocalBounds() const
{
	return mSprite.getLocalBounds();
}

void Animation::update(sf::Time dt)
{
    if (!isFinished()) //If the animation is finished, no need to update it
    {
        sf::Time timePerFrame = mDuration / static_cast<float>(mFrames.size());
        mElapsedTime += dt;

        // While we have a frame to process
        while (mElapsedTime >= timePerFrame and !isFinished())
        {
            mElapsedTime -= timePerFrame;
            if (mRepeat) //If the animation repeats and the next frame equals the size, make it the first
                mCurrentFrame = (mCurrentFrame + 1) % mFrames.size();
            else
                mCurrentFrame++; //If the animation doesn't repeat, increment it simply (it will go off the array after mDuration)

            if (!isFinished()) //If the current frame index isn't out of the array, set the texture rect and origin
            {
                mSprite.setTextureRect(mFrames.at(mCurrentFrame).textureRect);
                mSprite.setOrigin(mFrames.at(mCurrentFrame).origin);
            }
        }
    }
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

Animation::Frame::Frame(sf::IntRect textureRect, sf::Vector2f origin)
: textureRect(textureRect)
, origin(origin)
{

}

Animation::Frame::~Frame()
{

}

}
