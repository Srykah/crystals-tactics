#include "Graphism/Scene/Scene.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include "Graphism/Scene/Node.hpp"
#include <sstream>

namespace Graphism
{

Scene::Scene()
: mKey(-1)
{

}

Scene::~Scene()
{

}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const Node::Ptr& elem : mNodes)
    {
        if (elem->isVisible())
        target.draw(*elem, states);
    }
}

void Scene::update(sf::Time delta)
{
    bool sortNeeded(false);
    for (Node::Ptr& elem : mNodes)
        sortNeeded = sortNeeded || elem->update(delta);

    if(sortNeeded)
        sort();
}

Node::Key Scene::addNode(Node* node)
{
    mKey++;
    node->mScene = this;
    node->mKey = mKey;
    mNodes.emplace_back(node);
    sort();
    return mKey;
}

Node* Scene::getNode(Node::Key key)
{
    auto it = std::find_if(mNodes.begin(), mNodes.end(), [key](const Node::Ptr& elem){ return elem->getKey() == key; });
    if (it != mNodes.end())
        return it->get();
    else
    {
        std::stringstream ss;
        ss << "Graphism::Scene::getNode : Key " << key << " not in Scene";
        throw std::out_of_range(ss.str());
    }
}

void Scene::removeNode(Node::Key key)
{
    auto it = std::find_if(mNodes.begin(), mNodes.end(), [key](const Node::Ptr& elem){ return elem->getKey() == key; });
    if (it != mNodes.end())
    {
        mNodes.erase(it);
        std::for_each(mNodes.begin(), mNodes.end(),
            [this, it](const Node::Ptr& elem){ if (elem->getParent() == it->get()) removeNode(elem->getKey()); });
    }
}

void Scene::sort()
{
    if (!std::is_sorted(mNodes.begin(), mNodes.end(),
              [](const Node::Ptr& left, const Node::Ptr& right){ return left->getZ() < right->getZ(); }))
    std::sort(mNodes.begin(), mNodes.end(),
              [](const Node::Ptr& left, const Node::Ptr& right){ return left->getZ() < right->getZ(); });
}

}
