#include "Graphism/Scene/NoOwnNode.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

Graphism::NoOwnNode::NoOwnNode(sf::Drawable* drawable, float z, Key parentKey)
: Node(z, parentKey)
, mDrawable(drawable)
{

}

Graphism::NoOwnNode::~NoOwnNode()
{

}

void Graphism::NoOwnNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RenderStates newStates(states);
    newStates.transform *= getGlobalTransform();
    target.draw(*mDrawable, newStates);
}
