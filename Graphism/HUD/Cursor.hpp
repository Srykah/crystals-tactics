#ifndef CURSOR_HPP_INCLUDED
#define CURSOR_HPP_INCLUDED

#include "Graphism/Scene/EntityNode.hpp"
#include <SFML/System/Vector2.hpp>

namespace Graphism
{

class Cursor
{
public:
    Cursor();
    ~Cursor();

private:
    EntityNode*     mCursorFront, mCursorBack;
    sf::Vector2i    mCursorCoords;
};

}

#endif // CURSOR_HPP_INCLUDED
