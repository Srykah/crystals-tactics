#include "../Gameplay/Element.hpp"

Affinities neutralAffinities()
{
    Affinities aff;

    aff[Air] = 1.f;
    aff[Water] = 1.f;
    aff[Fire] = 1.f;
    aff[Electricity] = 1.f;
    aff[Rust] = 1.f;

    return aff;
}
