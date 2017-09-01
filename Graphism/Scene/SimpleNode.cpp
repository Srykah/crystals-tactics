#include "Graphism/Scene/SimpleNode.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace Graphism
{

SimpleNode::SimpleNode(sf::Drawable* drawable, float z, Key parentKey)
: Node(z, parentKey)
, mDrawable(drawable)
{

}

SimpleNode::~SimpleNode()
{

}

void SimpleNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getGlobalTransform();
    target.draw(*mDrawable, states);
}

}
