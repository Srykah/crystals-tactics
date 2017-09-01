#include "Data/Graphism/EntityData.hpp"
#include "Gameplay/General/Routines.hpp"
#include <stdexcept>
//#include <iostream>

using Direction::Dir;

namespace Data
{

bool EntityData::loadFromNode(const pugi::xml_node& node)
{
    sf::String textureFilename(node.attribute("spritesheet").as_string());
    if (!mSpriteSheet.loadFromFile(textureFilename))
    {
        throw std::runtime_error(sf::String("Error with texture " ) + textureFilename);
        return false;
    }

    for (auto animNode : node.children("animation"))
    {
        sf::String animName(animNode.attribute("name").as_string());
        //std::cerr << "loading animation " << animName << " :" << std::endl;

        bool repeat(animNode.attribute("repeat").as_bool());
        sf::Time duration(sf::milliseconds(animNode.attribute("duration").as_int()));

        for (auto facingNode : animNode.children())
        {
            //std::cerr << "    loading facing " << facingNode.name() << std::endl;
            Direction::Dir facing(StrToDir(facingNode.name()));
            mData.emplace_back(animName, facing, AnimationData(mSpriteSheet, duration, repeat));
        }
    }

    return true;
}

bool EntityData::loadFromFile(const sf::String& filename)
{
    pugi::xml_document doc;
    if (!doc.load_file(filename.toAnsiString().c_str()))
        return false;

    return loadFromNode(doc.child("entity"));
}

const AnimationData& EntityData::getAnim(const sf::String& animName, Direction::Dir facing) const
{
    auto it = std::find_if(mData.begin(), mData.end(),
                           [animName, facing](const EntityAnimData& anim){ return anim.name == animName && anim.facing == facing; });
    if (it == mData.end())
    {
        std::stringstream ss;
        ss << "No entity data for anim " << animName.toAnsiString() << " with facing " << DirToStr(facing).toAnsiString();
        throw std::runtime_error(ss.str());
    }
    else
        return it->data;
}

}
