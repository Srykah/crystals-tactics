#include "Data/Gameplay/AbilityHolder.hpp"
#include <stdexcept>

namespace Data
{

AbilityHolder::AbilityHolder()
{
    //push_back every abilities in the game here.
}

Ab::Ability& AbilityHolder::get(CharType type, short id, bool mech)
{
    auto it = std::find_if(mDataTab.begin(), mDataTab.end(), [type, mech, id](const AbData& abData)
    {
        return type == abData.type && mech == abData.mech && id == abData.id;
    });

    if (it == mDataTab.end())
        throw std::out_of_range("AbilityHolder : Out of Range");
    else
        return *(it->ability);
}

const Ab::Ability& AbilityHolder::get(CharType type, short id, bool mech) const
{
    auto it = std::find_if(mDataTab.begin(), mDataTab.end(), [type, mech, id](const AbData& abData)
    {
        return type == abData.type && mech == abData.mech && id == abData.id;
    });

    if (it == mDataTab.end())
        throw std::out_of_range("AbilityHolder : Out of Range");
    else
        return *(it->ability);
}

}
