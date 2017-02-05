#include "../Graphism/Scene.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

Graphism::Scene::Child::Child(const sf::Drawable* drawable, float z)
: drawable(drawable)
, z(z)
{

}

Graphism::Scene::Scene()
: mCurrentKey(0)
{

}

Graphism::Scene::~Scene()
{

}

void Graphism::Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const Pair& elem : mChildren)
        target.draw(*elem.first.drawable, states);
}

Graphism::Scene::Key Graphism::Scene::addChild(Child child)
{
    mChildren.push_back(std::make_pair(child, mCurrentKey));
    std::sort(mChildren.begin(), mChildren.end(), [](const Pair left, const Pair right){ return left.first.z <= right.first.z; });
    mCurrentKey++;
    return mCurrentKey-1;
}

void Graphism::Scene::setZ(Graphism::Scene::Key key, float z)
{
    auto it = std::find_if(mChildren.begin(), mChildren.end(), [key](std::pair<Child, Key>& elem){ return elem.second == key; });
    it->first.z = z;
    std::sort(mChildren.begin(), mChildren.end(), [](const Pair left, const Pair right){ return left.first.z <= right.first.z; });
}

void Graphism::Scene::removeChild(Key key)
{
    auto it = std::find_if(mChildren.begin(), mChildren.end(), [key](std::pair<Child,Key>& elem){ return elem.second == key; });
    if (it != mChildren.end())
        mChildren.erase(it);
}
