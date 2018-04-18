
template <class Resource>
void ResourceHolder<Resource>::load(const sf::String& filename)
{
	// open document
	pugi::xml_document doc;
    if (!doc.load_file(file.toAnsiString().c_str()))
        throw std::runtime_error(sf::String("Error : couldn't open ") + file);

    // for each child, create a resource and use its load method on the child
    for (const pugi::xml_node& child : node.children())
    {
        short id = child.attribute("id").as_int();
        if (id > mResources.size())
            mResources.resize(id);
        mResources.at(id)->load(child);
    }
}

template <class Resource>
void ResourceHolder<Resource>::load(const sf::String& filename, LoadingFun fun)
{
    // open document
	pugi::xml_document doc;
    if (!doc.load_file(file.toAnsiString().c_str()))
        throw std::runtime_error(sf::String("Error : couldn't open ") + file);

    // for each child, use the load method given as parameter
    for(const pugi::xml_node& child : node.children())
    {
        short id = child.attribute("id").as_int();
        if (id > mResources.size())
            mResources.resize(id);
        mResources.at(id).reset(fun(child));
    }
}

template <class Resource>
Resource& ResourceHolder<Resource>::get(short id)
{
	return *mResources.at(id);
}

template <class Resource>
const Resource& ResourceHolder<Resource>::get(short id) const
{
	return *mResources.at(id);
}
