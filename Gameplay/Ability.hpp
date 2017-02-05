#ifndef ABILITY_HPP_INCLUDED
#define ABILITY_HPP_INCLUDED

#include "../Data/AbilityData.hpp"
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <functional>
#include <map>
#include <memory>

class Character;
class Battlefield;

class Ability
{
public:
    typedef std::unique_ptr<Ability> Ptr;

public:
                                        Ability(Character* user, const Data::AbilityData& data);
    virtual                             ~Ability();

    virtual void                        update(sf::Time delta);
    virtual const sf::String&           getName() const; // ok
    virtual const sf::String&           getDescription() const; // ok
    virtual std::vector<sf::Vector2i>   getRange() const; // ok
    virtual std::vector<sf::Vector2i>   getArea(sf::Vector2i to) const; // ok
            bool                        isAvailable() const; // ok
            short                       getCounter() const; // ok
            void                        use(sf::Vector2i to);
            void                        incrementCounter(); // ok
            bool                        inProgress() const;

protected:
    const Data::AbilityData& mData;
    Character*      mUser;
    sf::Vector2i    mTile;
    short           mCounter;
};

#endif // ABILITY_HPP_INCLUDED
