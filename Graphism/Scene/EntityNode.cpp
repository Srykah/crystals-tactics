#include "Graphism/Scene/EntityNode.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace gr
{

EntityNode::EntityNode(Entity* entity, float z, Node* parent)
: Node(z, parent)
, entity(entity)
{

}

EntityNode::~EntityNode()
{

}

void EntityNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getGlobalTransform();
    target.draw(*entity, states);
}

bool EntityNode::update(sf::Time delta)
{
    entity->update(delta);

    return Node::update(delta);
}

}
