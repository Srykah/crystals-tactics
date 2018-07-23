#include "Graphism/HUD/Cursor.hpp"
#include "Gameplay/General/Routines.hpp"
#include "Gameplay/Battle/Battlefield.hpp"

namespace gr
{

Cursor::Cursor(Scene& scene, const dt::EntityHolder& entities, sf::Vector2i coords)
: mNode(nullptr)
, mCoords(coords)
{
    mNode = new EntityNode(new Entity(entities.get(Entities::CursorTile), "fixed", Direction::None), coords.y+1);
    scene.addNode(mNode);

    EntityNode* arrowNode = new EntityNode(new Entity(entities.get(Entities::Arrow), "float", Direction::Down), 100.f, mNode);
    arrowNode->move(0.f, -2*TILE_DIM);
    scene.addNode(arrowNode);

    updateEntityPositions();
}

Cursor::~Cursor()
{

}

bool Cursor::setCoords(sf::Vector2i coords)
{
    bool needToSortScene = (coords.y != mCoords.y);
    mCoords = coords;
    updateEntityPositions();
    return needToSortScene;
}

bool Cursor::move(sf::Vector2i offset)
{
    return setCoords(getCoords()+offset);
}

sf::Vector2i Cursor::getCoords() const
{
    return mCoords;
}

sf::View Cursor::getView(float zoom)
{
    return sf::View(mNode->getPosition(), sf::Vector2f(1366.f, 768.f)/zoom);
}

void Cursor::updateEntityPositions()
{
    mNode->setPosition(get2DPos(mCoords));
    mNode->setZ(mCoords.y+1);
}

void Cursor::setVisible(bool visible)
{
    mNode->setVisible(visible);
}

}
