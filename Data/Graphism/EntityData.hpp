#ifndef ENTITYDATA_HPP_INCLUDED
#define ENTITYDATA_HPP_INCLUDED

#include <SFML/System/String.hpp>
#include <vector>
#include "Data/Graphism/AnimationData.hpp"
#include "Gameplay/General/Direction.hpp"

namespace Data
{

class EntityData
{
public:
    bool loadFromNode(const pugi::xml_node& node);
    bool loadFromFile(const sf::String& filename);

    //const sf::Texture&      getTexture() const;
    const AnimationData&    getAnim(const sf::String& anim, Direction::Dir facing) const;

private:
    struct EntityAnimData
    {
        EntityAnimData(const sf::String& name, Direction::Dir facing, const AnimationData& data) :
            name(name), facing(facing), data(data) {}

        sf::String name;
        Direction::Dir facing;
        AnimationData data;
    };

private:
    sf::Texture mSpriteSheet;
    std::vector<EntityAnimData> mData;
};

}

#endif // ENTITYDATA_HPP_INCLUDED
