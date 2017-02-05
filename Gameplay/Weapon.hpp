#ifndef WEAPON_HPP_INCLUDED
#define WEAPON_HPP_INCLUDED

#include "../Data/GameDataIdentifiers.hpp"
#include "../Gameplay/Stats.hpp"
#include <memory>
#include <SFML/System/String.hpp>

class Weapon
{
public:
    typedef std::shared_ptr< Weapon > SPtr;

    enum Type
    {
        Sword,
        Dagger,
        Crossbow,
        Gun
    };

    Weapon(Type type, Weapons::ID id,
           const sf::String& name, const sf::String& description,
           float damage, int range,
           Stats stats);
    ~Weapon();

    Type                getType() const;
    bool                isMelee() const;
    Weapons::ID         getID() const;
    const sf::String&   getName() const;
    const sf::String&   getDescription() const;
    float               getDamage() const;
    int                 getRange() const;
    Stats               getStats() const;

private:
    Type mType;
    Weapons::ID mID;
    sf::String mName;
    sf::String mDescription;
    float mDamage;
    int mRange;
    Stats mStats;
};


#endif // WEAPON_HPP_INCLUDED
