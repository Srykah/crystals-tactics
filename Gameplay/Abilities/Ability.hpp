#ifndef ABILITY_HPP_INCLUDED
#define ABILITY_HPP_INCLUDED

#include "Gameplay/Cutscene/Cutscene.hpp"
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <functional>
#include <map>
#include <memory>
#include <bitset>

class Character;
class Battlefield;

namespace ab {

class Ability
{
public:
    typedef std::unique_ptr<Ability> Ptr;

public:
                                        Ability(const sf::String& name, const sf::String& desc, short cooldown);
    virtual                             ~Ability();

            const sf::String&           getName() const;
            const sf::String&           getDescription() const;
            short                       getCooldown() const;
    virtual std::vector<sf::Vector2i>   getRange(Character* user) const = 0;
    virtual std::vector<sf::Vector2i>   getArea(Character* user, sf::Vector2i to) const = 0;
    virtual void                        use(Character* user, sf::Vector2i to) const = 0;

private:
    sf::String  mName, mDescription;
    short       mCooldown;
};

}

#endif // ABILITY_HPP_INCLUDED
