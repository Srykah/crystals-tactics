#include "Gameplay/Cutscene/CutsceneEvent.hpp"
#include "Gameplay/Character/Character.hpp"

CutsceneEvent::CutsceneEvent(Trigger on_start, Update on_update, Trigger on_end)
: mStart(on_start)
, mEnd(on_end)
, mUpdate(on_update)
{

}

CutsceneEvent::CutsceneEvent(Trigger on_start, const sf::Time countdown, Trigger on_end)
: mCountdown(countdown)
, mStart(on_start)
, mEnd(on_end)
{

}

CutsceneEvent::CutsceneEvent(Character* charac, std::string anim, Direction::Dir facing)
: mStart([charac, anim, facing](){ charac->getEntity()->setAnimationAndFacing(anim, facing); })
, mUpdate([charac](sf::Time delta){ return charac->getEntity()->isAnimationFinished(); })
{

}

CutsceneEvent::~CutsceneEvent()
{

}

void CutsceneEvent::onStart()
{
    mStart();
}

bool CutsceneEvent::update(sf::Time delta)
{
    mTimer += delta;
    return (mCountdown != sf::Time::Zero && mTimer >= mCountdown) || mUpdate(delta);
}

void CutsceneEvent::onEnd()
{
    mEnd();
}
