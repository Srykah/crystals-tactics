#include "Graphism/Entity/AnimationData.hpp"

namespace en
{

Animationdt::AnimationData(const sf::Texture& texture, sf::Time duration, bool repeat)
: texture(texture)
, duration(duration)
, repeat(repeat)
{

}

void Animationdt::loadFromNode(const pugi::xml_node& node)
{
    for (auto frame : node.children())
    {
        sf::IntRect rect;
        sf::Vector2f origin;

        rect.left = frame.child("rect").attribute("left").as_int();
        rect.top = frame.child("rect").attribute("top").as_int();
        rect.width = frame.child("rect").attribute("width").as_int();
        rect.height = frame.child("rect").attribute("height").as_int();

        origin.x = frame.child("origin").attribute("x").as_int();
        origin.y = frame.child("origin").attribute("y").as_int();

        frames.push_back(Frame(rect, origin));
    }
}

std::size_t Animationdt::getNumFrames() const
{
	return frames.size();
}

}
