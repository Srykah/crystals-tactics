#ifndef EMPTYNODE_HPP_INCLUDED
#define EMPTYNODE_HPP_INCLUDED

#include "Graphism/Scene/Node.hpp"

namespace gr
{

class EmptyNode : public Node
{
public:
            EmptyNode(float z, Node* parent = nullptr);
    virtual ~EmptyNode();

    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;
};

}

#endif // EMPTYNODE_HPP_INCLUDED
