#include "Graphism/Scene/Scene.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include "Graphism/Scene/Node.hpp"
#include <stdexcept>

namespace gr
{

Scene::Scene()
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
        sortNeeded = elem->update(delta) || sortNeeded;

    if(sortNeeded)
        sort();
}

void Scene::addNode(Node* node)
{
    node->mScene = this;
    mNodes.emplace_back(node);
    sort();
}

void Scene::removeNode(Node* node)
{
    auto is_node = [node](const Node::Ptr& ptr){ return ptr.get() == node; };
    auto is_child = [node](const Node::Ptr& elem){ if (!elem) throw std::runtime_error("this node is empty");
        else return elem->getParent() == node; };

    auto it = std::find_if(mNodes.begin(), mNodes.end(), is_child);
    while (it != mNodes.end())
    {
        removeNode(it->get());
        it = std::find_if(mNodes.begin(), mNodes.end(), is_child);
    }

    auto it2 = std::remove_if(mNodes.begin(), mNodes.end(), is_node);
    if (it2 != mNodes.end())
        mNodes.erase(it2);
}

void Scene::sort()
{
    auto less_z = [](const Node::Ptr& left, const Node::Ptr& right){ return left->getZ() < right->getZ(); };

    if (!std::is_sorted(mNodes.begin(), mNodes.end(), less_z))
        std::sort(mNodes.begin(), mNodes.end(), less_z);
}

}
