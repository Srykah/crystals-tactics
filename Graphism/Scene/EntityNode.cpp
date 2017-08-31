#include "Graphism/Scene/EntityNode.hpp"

namespace Graphism
{

EntityNode::EntityNode(Entity* entity, float z, Key parentKey)
: Node(z, parentKey)
, entity(entity)
{

}

EntityNode::~EntityNode()
{

}

void EntityNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RenderStates newStates(states);
    newStates.transform *= getGlobalTransform();
    target.draw(*entity, states);
}

bool EntityNode::update(sf::Time delta)
{
    entity->update(delta);

    return Node::update(delta);
}

}
