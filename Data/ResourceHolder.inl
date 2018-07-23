
template <typename Resource>
void ResourceHolder<Resource>::load(const sf::String& file)
{
    pugi::xml_document doc;
    if (!doc.load_file(file.toAnsiString().c_str()))
        throw std::runtime_error(sf::String("Error : couldn't open ") + file);

    for(const pugi::xml_node& child : doc.first_child().children())
    {
        // Create and load resource
        std::unique_ptr<Resource> resource(new Resource());
        if (!resource->loadFromFile(child.attribute("filename").as_string()))
            throw std::runtime_error("ResourceHolder::load - Failed to load " + file);

        assert(mResourceMap.emplace(std::make_pair(child.attribute("id").as_string(), std::move(resource))).second);
    }
}

template <typename Resource>
Resource& ResourceHolder<Resource>::get(const std::string& id)
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}

template <typename Resource>
const Resource& ResourceHolder<Resource>::get(const std::string& id) const
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}
