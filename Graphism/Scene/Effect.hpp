#ifndef TRANSITION_HPP_INCLUDED
#define TRANSITION_HPP_INCLUDED

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>

typedef std::function<sf::Vector2f(sf::Time)>   PosFun;
typedef std::function<float(sf::Time)>          ZFun;
typedef std::function<float(sf::Time)>          RotFun;
typedef std::function<sf::Vector2f(sf::Time)>   ScaleFun;

namespace Graphism
{

class Node;

class Effect
{
public:
    // empty effect
    Effect();
    // any function
    Effect(sf::Time duration, PosFun posFun, ZFun zFun = ZFun(), RotFun rotFun = RotFun(), ScaleFun scaleFun = ScaleFun());
    // linear functions
    Effect(sf::Time duration, sf::Vector2f XYoffset, float Zoffset = 0.f, float rotation = 0.f, sf::Vector2f scaling = sf::Vector2f(1.f, 1.f));
    ~Effect();

    bool isFinished() const;

protected:
    bool        mIsEmpty;
    Node*       mNode;
    PosFun      mPosFun;
    ZFun        mZFun;
    RotFun      mRotFun;
    ScaleFun    mScaleFun;
    sf::Time    mTime, mDuration;

private:
    bool update(sf::Time delta);

    friend class Node;
};

}

#endif // TRANSITION_HPP_INCLUDED
