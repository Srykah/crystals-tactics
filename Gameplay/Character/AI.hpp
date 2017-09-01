#ifndef AI_HPP_INCLUDED
#define AI_HPP_INCLUDED

#include <SFML/System/Time.hpp>
#include <SFML/System/String.hpp>
#include "Gameplay/Battle/BattleContext.hpp"

class Character;

namespace AI
{

enum Type
{
    None,
    Balanced,
    Aggressive,
    Defensive
};

void playTurn(Character* unit);
void playTurnAggressive(Character* unit);
void playTurnDefensive(Character* unit);
void playTurnBalanced(Character* unit);

}

AI::Type StrToAI(const sf::String& str);

#endif // AI_HPP_INCLUDED
