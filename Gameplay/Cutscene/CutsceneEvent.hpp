#ifndef CUTSCENEEVENT_HPP_INCLUDED
#define CUTSCENEEVENT_HPP_INCLUDED

#include <SFML/System/Time.hpp>
#include <functional>
#include "Graphism/Entity/Animation.hpp"
#include "Gameplay/General/Direction.hpp"

class Character;

class CutsceneEvent
{
public:
    typedef std::function<void()> Trigger;
    typedef std::function<bool(sf::Time)> Update; //time needed for timed events
public:
    CutsceneEvent(Trigger on_start, Update on_update = [](sf::Time){return true;}, Trigger on_end = [](){});
    CutsceneEvent(Trigger on_start, const sf::Time countdown, Trigger on_end = [](){});
    CutsceneEvent(Character* charac, sf::String animName, Direction::Dir facing);
    ~CutsceneEvent();

    void onStart();
    bool update(sf::Time delta);
    void onEnd();

private:
    sf::Time mTimer;
    const sf::Time mCountdown;
    Trigger mStart, mEnd;
    Update mUpdate;
};


#endif // CUTSCENEEVENT_HPP_INCLUDED
