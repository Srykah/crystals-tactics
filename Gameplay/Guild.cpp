#include "../Gameplay/Guild.hpp"

void Guild::addMember(Character* member)
{
    mCharacters.emplace_back(member);
}

Character* Guild::getMember(int i)
{
    return mCharacters.at(i).get();
}

int Guild::getMemberCount() const
{
    return mCharacters.size();
}

Inventory* Guild::getInventory()
{
    return &mInventory;
}

