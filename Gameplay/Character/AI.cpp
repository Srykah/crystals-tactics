#include "Gameplay/Character/AI.hpp"
#include "Gameplay/Character/Character.hpp"

namespace AI
{

void playTurn(Character* unit)
{
    switch(unit->getAI())
    {
    case AI::Aggressive:
        playTurnAggressive(unit);
        break;

    case AI::Defensive:
        playTurnDefensive(unit);
        break;

    case AI::Balanced:
        playTurnBalanced(unit);
        break;

    case AI::None:
    default:
        break;
    }
}

void playTurnAggressive(Character* unit)
{

}

void playTurnDefensive(Character* unit)
{

}

void playTurnBalanced(Character* unit)
{

}

}

AI::Type StrToAI(const sf::String& str)
{
    if (str == "balanced")
        return AI::Balanced;
    else if (str == "aggressive")
        return AI::Aggressive;
    else if (str == "defensive")
        return AI::Defensive;
    else return AI::None;
}
