#ifndef ABILITYSET_HPP_INCLUDED
#define ABILITYSET_HPP_INCLUDED

#include <array>

class Ability;

namespace ch
{

struct AbilitySet
{
    static const char NB_ABILITIES = 4;

    AbilitySet() { for (int i(0); i < NB_ABILITIES; i++) abilities[i] = std::make_pair(nullptr, 0); }

    std::pair< Ability*, int > abilities[NB_ABILITIES];
};


}

#endif // ABILITYSET_HPP_INCLUDED
