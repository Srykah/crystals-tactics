#ifndef EVENT_HPP_INCLUDED
#define EVENT_HPP_INCLUDED

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include "Input/StdAction.hpp"

namespace Input
{

struct Event
{
    Event(sf::Event sfEvent = sf::Event(), StdAction stdAc = None, sf::Vector2i mousePos = sf::Vector2i()) :
        sfEvent(sfEvent), stdAc(stdAc), mousePos(mousePos) {}

    sf::Event sfEvent;
    StdAction stdAc;
    sf::Vector2i mousePos;
};

}

#endif // EVENT_HPP_INCLUDED
