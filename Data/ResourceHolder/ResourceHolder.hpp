#ifndef RESOURCEHOLDER_HPP_INCLUDED
#define RESOURCEHOLDER_HPP_INCLUDED

#include <map>
#include <SFML/System/String.hpp>
#include <memory>
#include <stdexcept>
#include <cassert>

namespace Data
{

template <typename Identifier, typename Resource>
class ResourceHolder
{
public:
    void						load(Identifier id, const sf::String& filename);

    template <typename Parameter>
    void						load(Identifier id, const sf::String& filename, const Parameter& secondParam);

    Resource&					get(Identifier id);
    const Resource&				get(Identifier id) const;

private:
    void						insertResource(Identifier id, std::unique_ptr<Resource> resource);


private:
    std::map<Identifier, std::unique_ptr<Resource>>	mResourceMap;
};

#include "ResourceHolder.inl"

}

#endif // RESOURCEHOLDER_HPP_INCLUDED
