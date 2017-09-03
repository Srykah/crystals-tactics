#include "Data/Gameplay/ConsumableHolder.hpp"

namespace Data
{

ConsumableHolder::ConsumableHolder()
{
    // load consumables in order here
}

Ab::Ability& ConsumableHolder::get(short id)
{
    return *(mDataTab.at(id));
}

const Ab::Ability& ConsumableHolder::get(short id) const
{
    return *(mDataTab.at(id));
}

}
