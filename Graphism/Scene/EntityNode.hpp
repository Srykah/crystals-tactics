#ifndef ENTITYNODE_HPP_INCLUDED
#define ENTITYNODE_HPP_INCLUDED

#include "Graphism/Scene/Node.hpp"
#include "Graphism/Entity/Entity.hpp"

namespace Graphism
{

struct EntityNode : public Node
{
            EntityNode(Entity* entity, float z, Key parentKey = -1);
    virtual ~EntityNode();

    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;
    bool update(sf::Time delta);

    Entity::Ptr entity;
};

}

#endif // ENTITYNODE_HPP_INCLUDED
