#ifndef STATUSAILMENT_HPP_INCLUDED
#define STATUSAILMENT_HPP_INCLUDED

#include <boost/variant.hpp>
#include <SFML/System/String.hpp>

enum StatusAilment
{
    None = -1,
    Burnt = 0,
    Poisoned,
    Bleeding,
    Rooted,
    Disabled,
    Asleep,
    Invisible,
    Count
};

typedef StatusAilment SA;

sf::String  SAToStr(SA ailment);
SA          StrToSA(const sf::String& text);

#endif // STATUSAILMENT_HPP_INCLUDED
