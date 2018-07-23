#ifndef DATAHOLDER_HPP_INCLUDED
#define DATAHOLDER_HPP_INCLUDED

#include "XML/pugixml.hpp"
#include <map>
#include <memory>
#include <SFML/System/String.hpp>

/** class DataHolder
 *
 *  Cette classe sert à stocker les métadonnées inscrites dans des fichiers XML :
 *  par exemple, les entités, les missions, les champs de bataille, etc.
 *
 *  La fonction de chargement ouvre le fichier dont le nom est passé en argument,
 *  crée les objets et appelle leur méthode load(pugi::xml_node) en passant les nodes du fichier.
 *
 *  Les données peuvent être récupérées par un ID.
 */

namespace dt {

template<typename DataType>
class DataHolder
{
public:
    void                load(const sf::String& file);
    DataType&		    get(const std::string& id);
    const DataType&	    get(const std::string& id) const;

private:
    std::map<std::string, std::unique_ptr<DataType> > mDataTab;
};

#include "DataHolder.inl"

}

#endif // DATAHOLDER_HPP_INCLUDED
