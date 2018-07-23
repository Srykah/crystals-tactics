#include "Gameplay/General/StatusAilment.hpp"

void StatusAilments::addAilment(StatusAilment ailment, int duration)
{
    mAilments[ailment] = getAilmentDuration(ailment) + duration;
}

bool StatusAilments::hasAilment(StatusAilment ailment) const
{
    return mAilments.count(ailment) && mAilments.at(ailment) > 0;
}

int StatusAilments::getAilmentDuration(StatusAilment ailment) const
{
    if (!hasAilment(ailment)) return 0;
    else return mAilments.at(ailment);
}

void StatusAilments::newTurn()
{
    for (int& duration : mAilments)
    {
        if (duration > 0)
            duration--;
    }
}

void StatusAilments::removeAilment(StatusAilment ailment)
{
    mAilments[ailments] = 0;
}

void StatusAilments::removeBadAilments()
{
    for (StatusAilment ailment : badAilments)
        removeAilment(ailment);
}

void StatusAilments::removeGoodAilments()
{
    for (StatusAilment ailment : goodAilments)
        removeAilment(ailment);
}

void StatusAilments::clear()
{
    mAilments.clear();
}
