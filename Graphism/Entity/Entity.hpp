#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <utility>
#include <string>
#include <memory>
#include "Data/Graphism/EntityData.hpp"
#include "Graphism/Entity/Animation.hpp"
#include "Gameplay/General/Direction.hpp"
#include "XML/pugixml.hpp"

namespace Graphism
{

class Entity : public sf::Drawable, public sf::Transformable
{
public:
    typedef std::unique_ptr<Entity> Ptr;

    Entity(const Data::EntityData& data);
    Entity(const Data::EntityData& data, std::string anim, Direction::Dir facing);
    ~Entity();

    void update(sf::Time delta);
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;

    void setAnimation(std::string anim);
    void setFacing(Direction::Dir facing);
    void setAnimationAndFacing(std::string anim, Direction::Dir facing);
    void restart();

    Direction::Dir getFacing() const;
    std::string getAnimationName() const;
    sf::Time getTimer() const;
    bool isAnimationFinished() const;

private:
    const Data::EntityData& mData;
    std::unique_ptr<Animation> mAnimationPtr;
    std::string mCurAnim;
    Direction::Dir mFacing;
};

}

#endif // ENTITY_HPP_INCLUDED
