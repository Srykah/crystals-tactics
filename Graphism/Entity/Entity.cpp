#include "Graphism/Entity/Entity.hpp"
#include "XML/pugixml.hpp"
#include <iostream>
#include <cassert>
#include <SFML/Graphics/RenderTarget.hpp>

namespace Graphism
{

Entity::Entity(const Data::EntityData& data, sf::String anim, Direction::Dir facing)
: mData(data)
, mCurAnim(anim)
, mFacing(facing)
{
    mAnimationPtr.reset(new Animation(mData.getAnim(mCurAnim, mFacing)));
}

Entity::~Entity()
{

}

void Entity::setAnimation(sf::String name)
{
    mCurAnim = name;
    mAnimationPtr.reset(new Animation(mData.getAnim(mCurAnim, mFacing)));
}

void Entity::setFacing(Direction::Dir facing)
{
    mFacing = facing;
    mAnimationPtr.reset(new Animation(mData.getAnim(mCurAnim, mFacing)));
}

void Entity::setAnimationAndFacing(sf::String anim, Direction::Dir facing)
{
    mCurAnim = anim;
    mFacing = facing;
    mAnimationPtr.reset(new Animation(mData.getAnim(mCurAnim, mFacing)));
}

void Entity::restart()
{
    mAnimationPtr->restart();
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*mAnimationPtr, states);
}

void Entity::update(sf::Time delta)
{
    mAnimationPtr->update(delta);
}

bool Entity::isAnimationFinished() const
{
    return mAnimationPtr->isFinished();
}

Direction::Dir Entity::getFacing() const
{
    return mFacing;
}

sf::String Entity::getAnimationName() const
{
    return mCurAnim;
}

sf::Time Entity::getTimer() const
{
    return mAnimationPtr->getElapsedTime();
}

}
