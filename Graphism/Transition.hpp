#ifndef TRANSITION_HPP_INCLUDED
#define TRANSITION_HPP_INCLUDED

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

namespace sf
{
    class Transformable;
}

namespace Graphism
{

class Transition
{
public:
    struct Transform
    {
        Transform(sf::Vector2f translate = sf::Vector2f(), float rotate = 0.f);

        sf::Vector2f translate;
        float rotate;
    };

    Transition(sf::Transformable* transformable = nullptr, Transition::Transform transform = Transition::Transform(), sf::Time time = sf::Time::Zero);
    ~Transition();

    void setTransformable(sf::Transformable* transformable);
    void update(sf::Time dt);
    bool isFinished() const;

private:
    sf::Transformable* mTransformable;
    Transition::Transform mTransform;
    sf::Time mTime;
    sf::Time mSpent;
};


}

#endif // TRANSITION_HPP_INCLUDED
