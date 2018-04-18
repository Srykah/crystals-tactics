#ifndef RESOURCEHOLDER_HPP_INCLUDED
#define RESOURCEHOLDER_HPP_INCLUDED

#include <map>
#include <SFML/System/String.hpp>
#include <memory>
#include <stdexcept>
#include <cassert>

namespace Data
{

template <class Resource>
class ResourceHolder
{
public:
    typedef std::function<Resource*(const pugi::xml_node& node)> LoadingFun;

public:
    void            load(const sf::String& filename); // for Resources that have a load(pugi::xml_node& node) method
    void			load(const sf::String& filename, LoadingFun fun); // for the other Resources

    Resource&		get(short id);
    const Resource&	get(short id) const;

private:
    std::vector< std::unique_ptr<Resource> >	mResources;
};

#include "ResourceHolder.inl"

}

#endif // RESOURCEHOLDER_HPP_INCLUDED
