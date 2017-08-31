#ifndef SCENE_HPP_INCLUDED
#define SCENE_HPP_INCLUDED

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>
#include <vector> // items need to be sorted according to drawing priority
#include "Graphism/Scene/Node.hpp"

namespace Graphism
{

class Scene : public sf::Drawable
{
public:
    Scene();
    ~Scene();

    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;
    void update(sf::Time delta);

    Node::Key addNode(Node* node);
    Node* getNode(Node::Key key); // returns pointer to the node with the key passed in argument
    void removeNode(Node::Key key); //removes children nodes recursively

private:
    void sort();

private:
    std::vector<Node::Ptr> mNodes;
    Node::Key mKey;
};

}


#endif // SCENE_HPP_INCLUDED
