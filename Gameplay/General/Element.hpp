#ifndef ELEMENT_HPP_INCLUDED
#define ELEMENT_HPP_INCLUDED

#include <SFML/System/String.hpp>
#include <map>
#include "XML/pugixml.hpp"

enum class Element
{
    None,
    Air,
    Water,
    Fire,
    Electricity,
    Rust
};

struct ElemAffinities
{
    ElemAffinities();
    ElemAffinities(float air, float water, float fire, float electricity, float rust);

    std::map<Element,float> aff;

    void load(const pugi::xml_node& node);

    ElemAffinities& operator*=(ElemAffinities const& other);
};

ElemAffinities operator*(ElemAffinities const& first, ElemAffinities const& second);

sf::String         ElementToStr(Element elem);
Element             StrToElement(const sf::String& text);

#endif // ELEMENT_HPP_INCLUDED
