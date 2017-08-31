#include "Gameplay/Cutscene/Cutscene.hpp"

Cutscene::Cutscene()
{

}

Cutscene::~Cutscene()
{

}

void Cutscene::addEvent(CutsceneEvent event)
{
    mEventQueue.push(event);
}

void Cutscene::update(sf::Time delta)
{
    if (!isEmpty())
    {
        if(!mEventQueue.front().update(delta))
        {
            mEventQueue.front().onEnd();
            mEventQueue.pop();
            if (!isEmpty())
                mEventQueue.front().onStart();
        }
    }
}

bool Cutscene::isEmpty() const
{
    return mEventQueue.empty();
}
