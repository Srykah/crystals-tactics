#include "Gameplay/Character/AI.hpp"
#include "Gameplay/Character/Character.hpp"

namespace
{

const ConversionMap<AI::Type, std::string> conversionMap = [](){
    ConversionMap<AI::Type, std::string> conversionMap;
    conversionMap.addPair(AI::Aggressive, "aggressive");
    conversionMap.addPair(AI::Defensive,  "defensive");
    conversionMap.addPair(AI::Balanced,   "balanced");
    conversionMap.addPair(AI::None,       "none");
    return conversionMap;
};

}

const ConversionMap<AI::Type, std::string>& getAIToStringMap() { return conversionMap; }

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
