#ifndef EQUIPMENT_HPP_INCLUDED
#define EQUIPMENT_HPP_INCLUDED

#include "../Data/GameDataIdentifiers.hpp"
#include "../Gameplay/Element.hpp"
#include "../Gameplay/Stats.hpp"
#include <memory>
#include <SFML/System/String.hpp>

class Equipment
{
public:
    enum Position
    {
        Head,
        Body,
        Feet,
        Accessory
    };

    enum Type
    {
        //Head
        Helmet,
        Hat,

        //Body
        LightArmor,
        HeavyArmor,

        //Feet
        Shoes,

        //Accessories
        Gloves
    };

    typedef std::shared_ptr< Equipment > SPtr;

    Equipment(Position position, Type type, Equipments::ID id,
              const sf::String& name, const sf::String& description,
              Stats stats, Affinities affinities = neutralAffinities());
    ~Equipment();

    Position            getPosition() const;
    Type                getType() const;
    Equipments::ID      getID() const;
    const sf::String&   getName() const;
    const sf::String&   getDescription() const;
    Stats               getStats() const;
    const Affinities&   getAffinities() const;

private:
    Position mPosition;
    Type mType;
    Equipments::ID mID;
    sf::String mName;
    sf::String mDescription;
    Stats mStats;
    Affinities mAffinities;
};


#endif // EQUIPMENT_HPP_INCLUDED
