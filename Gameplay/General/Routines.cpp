#include "Gameplay/General/Routines.hpp"
#include "Gameplay/Battle/Battlefield.hpp"
#include <stdexcept>

sf::Vector2f get2DPos(sf::Vector2i tile)
{
    return sf::Vector2f(TILE_DIM*(tile.x+0.5), TILE_DIM*(tile.y+0.5));
}

sf::Vector3f get3DPos(sf::Vector2i tile)
{
    return sf::Vector3f(TILE_DIM*(tile.x+0.5), TILE_DIM*(tile.y+0.5), tile.y);
}
