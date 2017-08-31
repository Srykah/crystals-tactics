#ifndef ABILITYHOLDER_HPP_INCLUDED
#define ABILITYHOLDER_HPP_INCLUDED

#include "Gameplay/Abilities/Ability.hpp"

namespace Data
{

class AbilityHolder
{
public:
    void                init();
    Ab::Ability&		get(short id);
    const Ab::Ability&	get(short id) const;

private:
    std::vector< Ab::Ability::Ptr > mDataTab;
};

}

#endif // ABILITYHOLDER_HPP_INCLUDED
