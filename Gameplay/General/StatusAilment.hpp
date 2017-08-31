#ifndef STATUSAILMENT_HPP_INCLUDED
#define STATUSAILMENT_HPP_INCLUDED

#include <boost/variant.hpp>

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

std::string SAToStr(SA ailment);
SA          StrToSA(const std::string& text);

#endif // STATUSAILMENT_HPP_INCLUDED
