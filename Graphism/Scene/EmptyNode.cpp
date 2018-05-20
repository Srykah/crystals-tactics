#include "Graphism/Scene/EmptyNode.hpp"

namespace gr
{

EmptyNode::EmptyNode(float z, Node* parent)
: Node(z, parent)
{

}

EmptyNode::~EmptyNode()
{

}

void EmptyNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}

}
