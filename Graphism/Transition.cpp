#include "../Graphism/Transition.hpp"
#include <SFML/Graphics/Transformable.hpp>

Graphism::Transition::Transform::Transform(sf::Vector2f translate, float rotate)
: translate(translate)
, rotate(rotate)
{

}

Graphism::Transition::Transition(sf::Transformable* transformable, Transform transform, sf::Time time)
: mTransformable(transformable)
, mTransform(transform)
, mTime(time)
, mSpent(sf::Time::Zero)
{

}

Graphism::Transition::~Transition()
{

}

void Graphism::Transition::setTransformable(sf::Transformable* transformable)
{
    mTransformable = transformable;
}

void Graphism::Transition::update(sf::Time dt)
{
    if (!isFinished() and mTransformable != nullptr)
    {
        if (mSpent + dt <= mTime)
        {
            mTransformable->move(mTransform.translate*(dt/mTime));
            mTransformable->rotate(mTransform.rotate*(dt/mTime));
            mSpent += dt;
        }
        else
        {
            mTransformable->move(mTransform.translate*((mTime - mSpent)/mTime));
            mTransformable->rotate(mTransform.rotate*((mTime - mSpent)/mTime));
            mSpent = mTime;
        }
    }
}

bool Graphism::Transition::isFinished() const
{
    return mSpent >= mTime;
}
