#include "Data/Gameplay/AbilityHolder.hpp"

namespace Data
{

void AbilityHolder::init()
{
    //push_back every single ability in the game here. And in the correct order please !
}

Ab::Ability& AbilityHolder::get(short id)
{
    return *(mDataTab.at(id));
}

const Ab::Ability& AbilityHolder::get(short id) const
{
    return *(mDataTab.at(id));
}

}
