#ifndef NOOWNNODE_HPP_INCLUDED
#define NOOWNNODE_HPP_INCLUDED

#include "Graphism/Scene/Node.hpp"

namespace Graphism
{

class NoOwnNode : public Node
{
public:
            NoOwnNode(sf::Drawable* drawable, float z, Node* parent = nullptr);
    virtual ~NoOwnNode();

    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;

private:
    sf::Drawable* mDrawable;
};

}

#endif // NOOWNNODE_HPP_INCLUDED
