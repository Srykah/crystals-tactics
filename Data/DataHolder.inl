#include <stdexcept>

template<typename DataType>
void DataHolder<DataType>::load(const sf::String& file)
{
    pugi::xml_document doc;
    if (!doc.load_file(file.toAnsiString().c_str()))
        throw std::runtime_error(sf::String("Error : couldn't open ") + file);

    for(const pugi::xml_node& child : doc.first_child().children())
    {
        std::unique_ptr<DataType> data(new DataType());
        data->load(child);
        mDataTab.emplace(child.attribute("id").as_string(), std::move(data));
    }
}

template<typename DataType>
DataType& DataHolder<DataType>::get(const std::string& id)
{
    return *(mDataTab.at(id));
}

template<typename DataType>
const DataType& DataHolder<DataType>::get(const std::string& id) const
{
    return *(mDataTab.at(id));
}
