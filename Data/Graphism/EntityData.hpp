#ifndef ENTITYDATA_HPP_INCLUDED
#define ENTITYDATA_HPP_INCLUDED

#include <string>
#include <vector>
#include "Data/Graphism/AnimationData.hpp"
#include "Gameplay/General/Direction.hpp"

namespace Data
{

class EntityData
{
public:
    bool loadFromNode(const pugi::xml_node& node);
    bool loadFromFile(const std::string& filename);

    //const sf::Texture&      getTexture() const;
    const AnimationData&    getAnim(const std::string& anim, Direction::Dir facing) const;

private:
    struct EntityAnimData
    {
        EntityAnimData(const std::string& name, Direction::Dir facing, const AnimationData& data) :
            name(name), facing(facing), data(data) {}

        std::string name;
        Direction::Dir facing;
        AnimationData data;
    };

private:
    sf::Texture mSpriteSheet;
    std::vector<EntityAnimData> mData;
};

}

#endif // ENTITYDATA_HPP_INCLUDED
