#ifndef ANIMATIONDATA_HPP_INCLUDED
#define ANIMATIONDATA_HPP_INCLUDED

#include <vector>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "XML/pugixml.hpp"

namespace Data
{

struct AnimationData
{
    struct Frame
    {
        Frame(sf::IntRect textureRect, sf::Vector2f origin) :
            textureRect(textureRect), origin(origin) {}

        sf::IntRect textureRect;
        sf::Vector2f origin;
    };


    AnimationData(const sf::Texture& texture, sf::Time duration = sf::Time::Zero, bool repeat = false);

    void loadFromNode(const pugi::xml_node& node);
    std::size_t getNumFrames() const;


    std::vector<Frame>  frames;
    const sf::Texture&  texture;
    sf::Time            duration;
    bool                repeat;
};


}

#endif // ANIMATIONDATA_HPP_INCLUDED
