#ifndef GAMEPLAYUTILITY_HPP_INCLUDED
#define GAMEPLAYUTILITY_HPP_INCLUDED

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

const int TILE_DIM(48);

sf::Vector2f        get2DPos(sf::Vector2i tile);
sf::Vector3f        get3DPos(sf::Vector2i tile);

#endif // GAMEPLAYUTILITY_HPP_INCLUDED
