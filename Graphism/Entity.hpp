#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <utility>
#include <string>
#include <memory>
#include "../Graphism/Animation.hpp"
#include "../Other/Direction.hpp"
#include "../Other/pugixml.hpp"

namespace Graphism
{

class Entity : public sf::Drawable, public sf::Transformable
{
public:
    Entity();
    ~Entity();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;
    bool loadFromNode(const pugi::xml_node& node);
    bool loadFromFile(std::string filename);
    void setAnimation(Animations::Type type);
    void setFacing(Direction::Dir facing);
    void setAnimationAndFacing(Animations::Type anim, Direction::Dir facing);
    Direction::Dir getFacing() const;
    void restart();
    void update(sf::Time delta);
    bool isAnimationFinished() const;

private:
    struct AnimStruct
    {
        AnimStruct(Animations::Type type, Direction::Dir facing, Animation::SPtr anim) :
            type(type), facing(facing), anim(anim) {}

        Animations::Type type;
        Direction::Dir facing;
        Animation::SPtr anim;
    };


private:
    std::shared_ptr<sf::Texture> mSpriteSheet;
    std::vector< AnimStruct > mAnimations;
    Animations::Type mCurAnim;
    Direction::Dir mFacing;
};

}

#endif // ENTITY_HPP_INCLUDED
