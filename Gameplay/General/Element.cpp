#include "Gameplay/General/Element.hpp"

ElemAffinities::ElemAffinities()
{
    aff[Element::Air] = 1.f;
    aff[Element::Water] = 1.f;
    aff[Element::Fire] = 1.f;
    aff[Element::Electricity] = 1.f;
    aff[Element::Rust] = 1.f;
}

ElemAffinities::ElemAffinities(float air, float water, float fire, float electricity, float rust)
{
    aff[Element::Air] = air;
    aff[Element::Water] = water;
    aff[Element::Fire] = fire;
    aff[Element::Electricity] = electricity;
    aff[Element::Rust] = rust;
}

void ElemAffinities::load(const pugi::xml_node& node)
{
    aff[Element::Air] = node.attribute("air").as_float(1.f);
    aff[Element::Water] = node.attribute("water").as_float(1.f);
    aff[Element::Fire] = node.attribute("fire").as_float(1.f);
    aff[Element::Electricity] = node.attribute("electricity").as_float(1.f);
    aff[Element::Rust] = node.attribute("rust").as_float(1.f);
}

ElemAffinities& ElemAffinities::operator*=(ElemAffinities const& other)
{
    aff[Element::Air] *= other.aff.at(Element::Air);
    aff[Element::Water] *= other.aff.at(Element::Water);
    aff[Element::Fire] *= other.aff.at(Element::Fire);
    aff[Element::Electricity] *= other.aff.at(Element::Electricity);
    aff[Element::Rust] *= other.aff.at(Element::Rust);

    return *this;
}

ElemAffinities operator*(ElemAffinities const& first, ElemAffinities const& second)
{
    return ElemAffinities(first) *= second;
}

std::string ElementToStr(Element elem)
{
    #define ELEMTOSTRING_CASE(ELEM) case Element::ELEM: return #ELEM;

    switch(elem)
    {
    ELEMTOSTRING_CASE(Air)
    ELEMTOSTRING_CASE(Water)
    ELEMTOSTRING_CASE(Fire)
    ELEMTOSTRING_CASE(Electricity)
    ELEMTOSTRING_CASE(Rust)

    default:
        return "None";
    }
}

Element StrToElement(const std::string& text)
{
    #define STRINGTOELEM_IF(TEXT, ELEM) if (TEXT == #ELEM) return Element::ELEM;

         STRINGTOELEM_IF(text, Air)
    else STRINGTOELEM_IF(text, Water)
    else STRINGTOELEM_IF(text, Fire)
    else STRINGTOELEM_IF(text, Electricity)
    else STRINGTOELEM_IF(text, Rust)
    else return Element::None;
}
