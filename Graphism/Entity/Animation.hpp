#ifndef ANIMATION_HPP_INCLUDED
#define ANIMATION_HPP_INCLUDED

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include <memory>
#include <vector>

#include "Graphism/Entity/AnimationData.hpp"

namespace gr
{

class Animation : public sf::Drawable
{
public:
                            Animation(const en::AnimationData& data);

    void 					update(sf::Time dt);
    void 					restart();

    sf::Time                getElapsedTime() const;
    bool 					isFinished() const;
    bool 					isRepeating() const;
    sf::Time                getDuration() const;
    sf::FloatRect 			getLocalBounds() const;

private:
    void 					draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    const en::AnimationData&    mAnimData;
    sf::Sprite 		            mSprite;
    std::size_t 		        mCurrentFrame;
    sf::Time                    mElapsedTime;
};

}

#endif // ANIMATION_HPP_INCLUDED
