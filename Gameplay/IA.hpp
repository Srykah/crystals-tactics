#ifndef IA_HPP_INCLUDED
#define IA_HPP_INCLUDED

#include <memory>
#include <SFML/System/Time.hpp>

class Character;

class IA
{
public:
    typedef std::shared_ptr<IA> SPtr;

    enum Type
    {
        None,
        Balanced,
        Aggressive,
        Defensive
    };

    IA(Character* charac, Type type = Type::None);
    ~IA();

    void setType(Type type);
    Type getType() const;

    void newTurn();
    void update(sf::Time delta);

private:
    Character* mCharac;
    Type mType;
    sf::Time mTime;
};

IA::Type convertStringToIA(std::string str);

#endif // IA_HPP_INCLUDED
