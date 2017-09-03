#ifndef ABILITYHOLDER_HPP_INCLUDED
#define ABILITYHOLDER_HPP_INCLUDED

#include "Gameplay/Abilities/Ability.hpp"
#include "Gameplay/Character/CharacterStructs.hpp"

namespace Data
{

class AbilityHolder
{
public:
    AbilityHolder();

    Ab::Ability&		get(CharType type, short id, bool mech = false);
    const Ab::Ability&	get(CharType type, short id, bool mech = false) const;

private:
    struct AbData
    {
        CharType type;
        bool mech;
        short id;
        Ab::Ability::Ptr ability;
    };

    std::vector<AbData> mDataTab;
};

}

#endif // ABILITYHOLDER_HPP_INCLUDED
