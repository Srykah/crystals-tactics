#include <stdexcept>

template<typename DataType>
void DataHolder<DataType>::loadFromNode(const pugi::xml_node& node)
{
    for(const pugi::xml_node& child : node.children())
    {
        mDataTab.emplace_back(new DataType());
        mDataTab.back()->load(child);
    }
}

template<typename DataType>
void DataHolder<DataType>::loadFromFile(const sf::String& file)
{
    pugi::xml_document doc;
    if (!doc.load_file(file.toAnsiString().c_str()))
        throw std::runtime_error(sf::String("Error : couldn't open ") + file);

    loadFromNode(doc.first_child());
}

template<typename DataType>
short DataHolder<DataType>::push_back(DataType* data)
{
    mDataTab.emplace_back(data);
    return mDataTab.size();
}

template<typename DataType>
DataType& DataHolder<DataType>::get(short id)
{
    return *(mDataTab.at(id));
}

template<typename DataType>
const DataType& DataHolder<DataType>::get(short id) const
{
    return *(mDataTab.at(id));
}
