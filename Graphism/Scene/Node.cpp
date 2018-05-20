#include "Graphism/Scene/Node.hpp"
#include "Graphism/Scene/Scene.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace gr
{

Node::Node(float z, Node* parentNode)
: mZ(z)
, mParent(parentNode)
, mScene(nullptr)
, mVisible(true)
{

}

Node::~Node()
{

}

bool Node::update(sf::Time delta)
{
    return mEffect.update(delta);
}

Node* Node::getParent() const
{
    return mParent;
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
    if (mParent == nullptr)
        return mZ;
    else
        return mZ + mParent->getZ();
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
    if (mParent == nullptr)
        return getRotation();
    else
        return getRotation() + mParent->getGlobalRotation();
}

sf::Vector2f Node::getGlobalScale() const
{
    if (mParent == nullptr)
        return getScale();
    else
    {
        sf::Vector2f prev_scale(mParent->getGlobalScale());
        return sf::Vector2f(getScale().x*prev_scale.x, getScale().y*prev_scale.y);
    }
}

sf::Transform Node::getGlobalTransform() const
{
    if (mParent == nullptr)
        return getTransform();
    else
        return mParent->getGlobalTransform() * getTransform();
}

void Node::setVisible(bool visible)
{
    mVisible = visible;
}

bool Node::isVisible() const
{
    return mVisible && (mParent == nullptr || mParent->isVisible());
}

}
