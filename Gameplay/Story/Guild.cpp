#include "Gameplay/Story/Guild.hpp"
#include "Other/Utility.hpp"

bool Guild::loadFromNode(const pugi::xml_node& node, States::Context context)
{
    /// units
    for (pugi::xml_node& unitNode : node.child("units").children())
        mCharacters.emplace_back(new Character(unitNode, context));

    /// inventory
    if (!mInventory.loadFromNode(node.child("inventory")))
        return false;

    /// job levels
    for (int i : getRange<CharType>())
    {
        pugi::xml_node data(node.child("jobLevels").child(CharTypeToStr(CharType(i)).c_str()));
        mJobLevels.emplace(CharType(i), JobLevel(data.attribute("level").as_int(1), data.attribute("exp").as_int()));
    }

    return true;
}

bool Guild::loadFromFile(const std::string& filename, States::Context context)
{
    pugi::xml_document doc;
    if (!doc.load_file(filename.c_str()))
        return false;

    return loadFromNode(doc.child("save"), context);
}

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

