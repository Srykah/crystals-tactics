#ifndef GAMEPLAYUTILITY_HPP_INCLUDED
#define GAMEPLAYUTILITY_HPP_INCLUDED

#include "../Gameplay/Character.hpp"
#include "../Other/ResourceIdentifiers.hpp"
#include <string>

std::string       convertTypeToString(Character::Type type);
Character::Type   convertStringToType(std::string text);
Entities::ID      convertTypeToEntitiesID(Character::Type type);

#endif // GAMEPLAYUTILITY_HPP_INCLUDED
