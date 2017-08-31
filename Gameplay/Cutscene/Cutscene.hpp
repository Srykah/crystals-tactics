#ifndef CUTSCENE_HPP_INCLUDED
#define CUTSCENE_HPP_INCLUDED

#include <queue>
#include "Gameplay/Cutscene/CutsceneEvent.hpp"

class Cutscene
{
public:

public:
    Cutscene();
    ~Cutscene();

    void addEvent(CutsceneEvent event);
    void update(sf::Time delta);
    bool isEmpty() const;

private:
    std::queue<CutsceneEvent> mEventQueue;
};

#endif // CUTSCENE_HPP_INCLUDED
