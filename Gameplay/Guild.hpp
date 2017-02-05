#ifndef GUILD_HPP_INCLUDED
#define GUILD_HPP_INCLUDED

#include <vector>
#include "../Gameplay/Character.hpp"
#include "../Gameplay/Inventory.hpp"

class Guild
{
public:
    void            addMember(Character* member);
    Character*      getMember(int i);
    int             getMemberCount() const;
    Inventory*      getInventory();

private:
    std::vector<Character::Ptr>    mCharacters;
    Inventory                       mInventory;
};



#endif // GUILD_HPP_INCLUDED
