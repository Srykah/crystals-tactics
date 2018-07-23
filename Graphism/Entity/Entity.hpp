#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include <SFML/Graphics/Drawable.hpp>
#include <utility>
#include <SFML/System/String.hpp>
#include <memory>
#include "Graphism/Entity/EntityData.hpp"
#include "Graphism/Entity/Animation.hpp"
#include "Gameplay/General/Direction.hpp"
#include "XML/pugixml.hpp"

namespace gr
{

class Entity : public sf::Drawable
{
public:
    typedef std::unique_ptr<Entity> Ptr;

    Entity(const en::EntityData& data, sf::String anim, Direction::Dir facing);
    ~Entity();

    void update(sf::Time delta);
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;

    void setAnimation(sf::String anim);
    void setFacing(Direction::Dir facing);
    void setAnimationAndFacing(sf::String anim, Direction::Dir facing);
    void restart();

    Direction::Dir getFacing() const;
    sf::String getAnimationName() const;
    sf::Time getTimer() const;
    bool isAnimationFinished() const;

private:
    const en::EntityData& mData;
    std::unique_ptr<Animation> mAnimationPtr;
    sf::String mCurAnim;
    Direction::Dir mFacing;
};

}

#endif // ENTITY_HPP_INCLUDED
