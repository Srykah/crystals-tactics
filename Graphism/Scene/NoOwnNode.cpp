#include "Graphism/Scene/NoOwnNode.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

gr::NoOwnNode::NoOwnNode(sf::Drawable* drawable, float z, Node* parent)
: Node(z, parent)
, mDrawable(drawable)
{

}

gr::NoOwnNode::~NoOwnNode()
{

}

void gr::NoOwnNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getGlobalTransform();
    target.draw(*mDrawable, states);
}
