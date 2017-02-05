#include "../GUI/Component.hpp"

namespace GUI
{

Component::Component()
: mIsSelected(false)
, mIsActive(false)
, mShortcut(sf::Keyboard::Unknown)
{
}

Component::~Component()
{
}

bool Component::isSelected() const
{
	return mIsSelected;
}

void Component::select()
{
    if (!isSelected())
    {
        mIsSelected = true;
    }
}

void Component::deselect()
{
    if (isSelected())
    {
        mIsSelected = false;
    }
}

bool Component::isActive() const
{
	return mIsActive;
}

void Component::activate()
{
	mIsActive = true;
}

void Component::deactivate()
{
	mIsActive = false;
}

void Component::setShortcut(sf::Keyboard::Key shortcut)
{

}

sf::Keyboard::Key Component::getShortcut() const
{
    return mShortcut;
}

}
