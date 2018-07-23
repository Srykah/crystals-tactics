#ifndef RESOURCEHOLDER_HPP_INCLUDED
#define RESOURCEHOLDER_HPP_INCLUDED

#include <map>
#include <SFML/System/String.hpp>
#include <memory>
#include <stdexcept>
#include <cassert>

/** class DataHolder
 *
 *  Cette classe sert à stocker les métadonnées inscrites dans des fichiers XML :
 *  par exemple, les entités, les missions, les champs de bataille, etc.
 *
 *  La fonction de chargement ouvre le fichier dont le nom est passé en argument,
 *  crée les objets et appelle leur méthode loadFromFile(std::string) en passant
 *  les noms de fichier contenus dans les nodes.
 *
 *  Les données peuvent être récupérées par un ID.
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
