#ifndef SIMPLENODE_HPP_INCLUDED
#define SIMPLENODE_HPP_INCLUDED

#include "Graphism/Scene/Node.hpp"
#include <memory>

namespace gr
{

class SimpleNode : public Node
{
public:
            SimpleNode(sf::Drawable* drawable, float z, Node* parent = nullptr);
    virtual ~SimpleNode();

    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;

private:
    std::unique_ptr<sf::Drawable> mDrawable;
};

}

#endif // SIMPLENODE_HPP_INCLUDED
