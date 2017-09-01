#include "Graphism/HUD/Cursor.hpp"
#include "Gameplay/General/Routines.hpp"

namespace Graphism
{

Cursor::Cursor(Scene& scene, const Data::EntityHolder& entities, sf::Vector2i coords)
: mCursorBack(new EntityNode(new Entity(entities.get(Entities::CursorBack), "idle", Direction::None), coords.y))
, mSceneKey(scene.addNode(mCursorBack))
, mCursorFront(new EntityNode(new Entity(entities.get(Entities::CursorFront), "float", Direction::None), 100.f, mSceneKey))
, mCursorCoords(coords)
{
    scene.addNode(mCursorFront);
    updateEntityPositions();
}

Cursor::~Cursor()
{

}

bool Cursor::setCoords(sf::Vector2i coords)
{
    bool needToSortScene = (coords.y != mCursorCoords.y);
    mCursorCoords = coords;
    updateEntityPositions();
    return needToSortScene;
}

sf::Vector2i Cursor::getCoords() const
{
    return mCursorCoords;
}

sf::View Cursor::getView(float zoom)
{
    return sf::View(get2DPos(mCursorCoords), sf::Vector2f(1366.f, 768.f)/zoom);
}

void Cursor::updateEntityPositions()
{
    mCursorBack->move(get2DPos(mCursorCoords));
    mCursorBack->setZ(mCursorCoords.y);
}


}
