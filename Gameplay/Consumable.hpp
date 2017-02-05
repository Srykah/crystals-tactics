#ifndef CONSUMABLE_HPP_INCLUDED
#define CONSUMABLE_HPP_INCLUDED

#include "../Data/GameDataIdentifiers.hpp"
#include <memory>
#include <SFML/System/String.hpp>

class Character;

class Consumable
{
public:
    typedef std::shared_ptr<Consumable> SPtr;

    Consumable(Consumables::ID id);
    ~Consumable();

    sf::String                  getName() const;
    sf::String                  getDescription() const;
    Consumables::ID             getID() const;
    /*
    std::vector<sf::Vector2i>   getRange(Character* user) const;
    std::vector<sf::Vector2i>   getArea(Character* user, sf::Vector2i to) const;
    void                        use(Character* user, sf::Vector2i to);
    void                        update(sf::Time delta);
    */
    bool                        isBeingUsed() const;

private:
    Consumables::ID mID;
};


#endif // CONSUMABLE_HPP_INCLUDED
