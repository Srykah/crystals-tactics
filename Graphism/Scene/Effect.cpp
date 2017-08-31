#include "Graphism/Scene/Effect.hpp"
#include "Graphism/Scene/Node.hpp"

namespace Graphism
{

Effect::Effect()
: mIsEmpty(true)
{

}

Effect::Effect(sf::Time duration, PosFun posFun, ZFun zFun, RotFun rotFun, ScaleFun scaleFun)
: mIsEmpty(false)
, mPosFun(posFun)
, mZFun(zFun)
, mRotFun(rotFun)
, mScaleFun(scaleFun)
, mDuration(duration)
{

}

Effect::Effect(sf::Time duration, sf::Vector2f XYoffset, float Zoffset, float rotation, sf::Vector2f scaling)
: Effect(duration,
    [XYoffset, duration](sf::Time t){ return (t/duration) * XYoffset; },
    [Zoffset,  duration](sf::Time t){ return (t/duration) * Zoffset;  },
    [rotation, duration](sf::Time t){ return (t/duration) * rotation; },
    [scaling,  duration](sf::Time t){ return (t/duration) * scaling;  })
{

}

Effect::~Effect()
{

}

bool Effect::update(sf::Time delta)
{
    if (!isFinished() && !mIsEmpty)
    {
        if (mTime + delta <= mDuration)
        {
            mNode->setPosition(mPosFun(mTime + delta));
            mNode->setRotation(mRotFun(mTime + delta));
            mNode->setZ(mZFun(mTime + delta));
            mNode->setScale(mScaleFun(mTime + delta));

            mTime += delta;

            return mZFun(mTime) != mZFun(mTime - delta);
        }
        else
            return update(mDuration - mTime);
    }

    return false;
}

bool Effect::isFinished() const
{
    return mTime >= mDuration;
}

}
