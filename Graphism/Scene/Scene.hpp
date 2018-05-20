#ifndef SCENE_HPP_INCLUDED
#define SCENE_HPP_INCLUDED

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>
#include <vector> // items need to be sorted according to drawing priority
#include "Graphism/Scene/Node.hpp"

namespace gr
{

class Scene : public sf::Drawable
{
public:
    Scene();
    ~Scene();

    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;
    void update(sf::Time delta);

    void addNode(Node* node);
    void removeNode(Node* node); //removes children nodes recursively

    void sort();

private:
    std::vector<Node::Ptr> mNodes;
};

}


#endif // SCENE_HPP_INCLUDED
