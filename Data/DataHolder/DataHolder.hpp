#ifndef DATAHOLDER_HPP_INCLUDED
#define DATAHOLDER_HPP_INCLUDED

#include "XML/pugixml.hpp"
#include <vector>
#include <memory>
#include <string>

namespace Data {

template<typename DataType>
class DataHolder
{
public:
    void                loadFromNode(const pugi::xml_node& node);
    void                loadFromFile(const std::string& file);
    short               push_back(DataType* data);
    DataType&		    get(short id);
    const DataType&	    get(short id) const;

private:
    std::vector< std::unique_ptr<DataType> > mDataTab;
};

#include "DataHolder.inl"

}

#endif // DATAHOLDER_HPP_INCLUDED
