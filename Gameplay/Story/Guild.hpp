#ifndef GUILD_HPP_INCLUDED
#define GUILD_HPP_INCLUDED

#include <vector>
#include <map>
#include "Gameplay/Character/Character.hpp"
#include "Gameplay/Items/Inventory.hpp"
#include "States/Arch/Context.hpp"

class Guild
{
public:
    struct JobLevel
    {
        JobLevel(short level = 1, short exp = 0) : level(level), exp(exp) {}
        short level, exp;
    };

public:
    bool            loadFromNode(const pugi::xml_node& node, States::Context context);
    bool            loadFromFile(const std::string& filename, States::Context context);

    void            addMember(Character* member);
    Character*      getMember(int i);
    int             getMemberCount() const;
    Inventory*      getInventory();

private:
    std::vector<Character::Ptr>         mCharacters;
    Inventory                           mInventory;
    std::map<CharType, JobLevel> mJobLevels;
};



#endif // GUILD_HPP_INCLUDED
