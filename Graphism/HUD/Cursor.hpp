#ifndef CURSOR_HPP_INCLUDED
#define CURSOR_HPP_INCLUDED

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/View.hpp>
#include "Graphism/Scene/EntityNode.hpp"
#include "Graphism/Scene/Scene.hpp"
#include "Data/ResourceHolder/ResourceIdentifiers.hpp"

namespace Graphism
{

class Cursor
{
public:
    Cursor(Scene& scene, const Data::EntityHolder& entities, sf::Vector2i coords = sf::Vector2i());
    ~Cursor();

    bool            setCoords(sf::Vector2i coords);
    sf::Vector2i    getCoords() const;
    sf::View        getView(float zoom = 1.f);

private:
    void            updateEntityPositions();

    EntityNode*     mCursorBack;
    Node::Key       mSceneKey;
    EntityNode*     mCursorFront;
    sf::Vector2i    mCursorCoords;
};

}

#endif // CURSOR_HPP_INCLUDED
