#ifndef SIGNAL_HPP_INCLUDED
#define SIGNAL_HPP_INCLUDED

#include <boost/variant.hpp>
#include <SFML/System/Vector2.hpp>

class Character;

namespace States
{

class State;

struct Signal
{
    typedef boost::variant<bool, short, int, float, sf::Vector2i, Character*> Data;

    State* sender;
    Data data;

    Signal(State* sender, Data data) : sender(sender), data(data) {};
};

}

#endif // SIGNAL_HPP_INCLUDED
