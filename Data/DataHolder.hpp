#ifndef DATAHOLDER_HPP_INCLUDED
#define DATAHOLDER_HPP_INCLUDED

#include "XML/pugixml.hpp"
#include <map>
#include <memory>
#include <SFML/System/String.hpp>

/** class DataHolder
 *
 *  Cette classe sert � stocker les m�tadonn�es inscrites dans des fichiers XML :
 *  par exemple, les entit�s, les missions, les champs de bataille, etc.
 *
 *  La fonction de chargement ouvre le fichier dont le nom est pass� en argument,
 *  cr�e les objets et appelle leur m�thode load(pugi::xml_node) en passant les nodes du fichier.
 *
 *  Les donn�es peuvent �tre r�cup�r�es par un ID.
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
