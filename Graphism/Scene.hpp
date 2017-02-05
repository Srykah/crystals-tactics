#ifndef SCENE_HPP_INCLUDED
#define SCENE_HPP_INCLUDED

#include <SFML/Graphics/Drawable.hpp>
#include <vector>

namespace Graphism
{

class Scene : public sf::Drawable
{
public:
    typedef short Key;

    struct Child
    {
        Child(const sf::Drawable* drawable, float z);

        const sf::Drawable* drawable;
        float z;
    };

    typedef std::pair<Child, Key> Pair;

    Scene();
    ~Scene();

    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;

    Key addChild(Child child);
    void setZ(Key key, float z);
    void removeChild(Key key);

private:
    std::vector<Pair> mChildren;
    Key mCurrentKey;
};

}


#endif // SCENE_HPP_INCLUDED
