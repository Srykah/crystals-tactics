#ifndef GAMEPLAYUTILITY_HPP_INCLUDED
#define GAMEPLAYUTILITY_HPP_INCLUDED

#include "Gameplay/Character/Character.hpp"
#include "Gameplay/General/Element.hpp"
#include "Gameplay/General/StatusAilment.hpp"
#include "Gameplay/General/Direction.hpp"
#include "Data/ResourceHolder/ResourceIdentifiers.hpp"
#include <string>

sf::Vector2f        get2DPos(sf::Vector2i tile);
sf::Vector3f        get3DPos(sf::Vector2i tile);

#endif // GAMEPLAYUTILITY_HPP_INCLUDED
