#ifndef ELEMENT_HPP_INCLUDED
#define ELEMENT_HPP_INCLUDED

#include <map>

enum Element
{
    None,
    Air,
    Water,
    Fire,
    Electricity,
    Rust
};

typedef std::map< Element, float > Affinities;

Affinities neutralAffinities();

#endif // ELEMENT_HPP_INCLUDED
