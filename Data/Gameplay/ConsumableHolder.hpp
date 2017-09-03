#ifndef CONSUMABLEHOLDER_HPP_INCLUDED
#define CONSUMABLEHOLDER_HPP_INCLUDED

#include "Gameplay/Abilities/Ability.hpp"

namespace Data
{

class ConsumableHolder
{
public:
    ConsumableHolder();
    Ab::Ability&		get(short id);
    const Ab::Ability&	get(short id) const;

private:
    std::vector< Ab::Ability::Ptr > mDataTab;
};

}

#endif // CONSUMABLEHOLDER_HPP_INCLUDED
