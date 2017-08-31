#ifndef SIMPLENODE_HPP_INCLUDED
#define SIMPLENODE_HPP_INCLUDED

#include "Graphism/Scene/Node.hpp"
#include <memory>

namespace Graphism
{

class SimpleNode : public Node
{
public:
            SimpleNode(sf::Drawable* drawable, float z, Key parentKey = -1);
    virtual ~SimpleNode();

    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;

private:
    std::unique_ptr<sf::Drawable> mDrawable;
};

}

#endif // SIMPLENODE_HPP_INCLUDED
