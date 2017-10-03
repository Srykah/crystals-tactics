#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>
#include <vector>
#include <memory>
#include "Graphism/Scene/Effect.hpp"

namespace Graphism
{

class Scene;

class Node : public sf::Drawable, public sf::Transformable
{
public:
    typedef int32_t Key;
    typedef std::unique_ptr< Node > Ptr;

public:
                    Node(float z, Node* parentNode = nullptr);
    virtual         ~Node();

    virtual bool    update(sf::Time delta);

    Key             getKey() const;
    Node*           getParent() const;

    void            setZ(float z);
    void            moveZ(float offset);
    float           getZ()               const;

    void            setEffect(Effect effect);
    bool            isEffectFinished() const;

    sf::Vector2f    getGlobalPosition()  const;
    float           getGlobalRotation()  const;
    sf::Vector2f    getGlobalScale()     const;
    sf::Transform   getGlobalTransform() const;

    void            setVisible(bool visible = true);
    bool            isVisible() const;

private:
    Key     mKey;
    float   mZ;
    Node*   mParent;
    Scene*  mScene;
    Effect  mEffect;
    bool    mVisible;

    friend class Scene;
};

}

#endif // NODE_HPP_INCLUDED
