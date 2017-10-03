#include "Graphism/Scene/NoOwnNode.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

Graphism::NoOwnNode::NoOwnNode(sf::Drawable* drawable, float z, Node* parent)
: Node(z, parent)
, mDrawable(drawable)
{

}

Graphism::NoOwnNode::~NoOwnNode()
{

}

void Graphism::NoOwnNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getGlobalTransform();
    target.draw(*mDrawable, states);
}
