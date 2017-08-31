#include "Gameplay/Items/QuestItem.hpp"

QuestItem::QuestItem(int id, const sf::String& name, const sf::String& description)
: mID(id)
, mName(name)
, mDescription(description)
{

}

QuestItem::~QuestItem()
{

}

int QuestItem::getID() const
{
    return mID;
}

const sf::String& QuestItem::getName() const
{
    return mName;
}

const sf::String& QuestItem::getDescription() const
{
    return mDescription;
}
