#ifndef QUESTITEM_HPP_INCLUDED
#define QUESTITEM_HPP_INCLUDED

#include <memory>
#include <SFML/System/String.hpp>

class QuestItem
{
public:
    typedef std::shared_ptr< QuestItem > SPtr;

    QuestItem(int id, const sf::String& name, const sf::String& description);
    ~QuestItem();

    int                 getID() const;
    const sf::String&   getName() const;
    const sf::String&   getDescription() const;

private:
    int mID;
    sf::String mName;
    sf::String mDescription;
};

#endif // QUESTITEM_HPP_INCLUDED
