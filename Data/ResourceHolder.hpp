#ifndef RESOURCEHOLDER_HPP_INCLUDED
#define RESOURCEHOLDER_HPP_INCLUDED

#include <map>
#include <SFML/System/String.hpp>
#include <memory>
#include <stdexcept>
#include <cassert>

/** class DataHolder
 *
 *  Cette classe sert � stocker les m�tadonn�es inscrites dans des fichiers XML :
 *  par exemple, les entit�s, les missions, les champs de bataille, etc.
 *
 *  La fonction de chargement ouvre le fichier dont le nom est pass� en argument,
 *  cr�e les objets et appelle leur m�thode loadFromFile(std::string) en passant
 *  les noms de fichier contenus dans les nodes.
 *
 *  Les donn�es peuvent �tre r�cup�r�es par un ID.
 */

namespace dt
{

template <typename Resource>
class ResourceHolder
{
public:
    void						load(const sf::String& file);

    Resource&					get(const std::string& id);
    const Resource&				get(const std::string& id) const;


private:
    std::map<std::string, std::unique_ptr<Resource>>	mResourceMap;
};

#include "ResourceHolder.inl"

}

#endif // RESOURCEHOLDER_HPP_INCLUDED
