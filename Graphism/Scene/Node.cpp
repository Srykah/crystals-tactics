#include "Graphism/Scene/Node.hpp"
#include "Graphism/Scene/Scene.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace Graphism
{

Node::Node(float z, Node::Key parentKey)
: mKey(-1)
, mZ(z)
, mParentKey(parentKey)
, mScene(nullptr)
{

}

Node::~Node()
{

}

bool Node::update(sf::Time delta)
{
    return mEffect.update(delta);
}

Node::Key Node::getKey() const
{
    return mKey;
}

Node::Key Node::getParentKey() const
{
    return mParentKey;
}

void Node::setZ(float z)
{
    mZ = z;
}

void Node::moveZ(float offset)
{
    mZ += offset;
}

float Node::getZ() const
{
    if (mParentKey == -1)
        return mZ;
    else
        return mZ + mScene->getNode(mParentKey)->getZ();
}

void Node::setEffect(Effect effect)
{
    mEffect = effect;
    mEffect.mNode = this;
}

bool Node::isEffectFinished() const
{
    return mEffect.isFinished();
}

sf::Vector2f Node::getGlobalPosition() const
{
    return getGlobalTransform().transformPoint(sf::Vector2f());
}

float Node::getGlobalRotation() const
{
    if (mParentKey == -1)
        return getRotation();
    else
        return getRotation() + mScene->getNode(mParentKey)->getGlobalRotation();
}

sf::Vector2f Node::getGlobalScale() const
{
    if (mParentKey == -1)
        return getScale();
    else
    {
        sf::Vector2f prev_scale(mScene->getNode(mParentKey)->getGlobalScale());
        return sf::Vector2f(getScale().x*prev_scale.x, getScale().y*prev_scale.y);
    }
}

sf::Transform Node::getGlobalTransform() const
{
    if (mParentKey == -1)
        return getTransform();
    else
        return mScene->getNode(mParentKey)->getGlobalTransform() * getTransform();
}

}
