#include "../GUI/Container.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

Container::Container()
: mChildren()
, mSelectedChild(-1)
{
}

void Container::pack(Component::SPtr component)
{
	mChildren.push_back(component);
	if(!hasSelection())
        selectIndex(0);
}

int Container::getSelectionIndex() const
{
    return mSelectedChild;
}

void Container::activateSelection()
{
    if (hasSelection())
        mChildren[mSelectedChild]->activate();
}

bool Container::isSelectable() const
{
    return true;
}

/** contains(...) : deux fonctions pour savoir si l'un des composants contient le point.
 * on boucle pour appeler les fonctions contains() des composants.
 */
bool Container::contains(sf::Vector2f point) const
{
    for (int i(0); i < mChildren.size(); ++i)
    {
        if (mChildren[i]->contains(point))
            return true;
    }

    return false;
}

bool Container::contains(float x, float y) const
{
    return contains(sf::Vector2f(x,y));
}

bool Container::handleInput(const sf::Event& event, IH::SA stdAc, sf::Vector2f mousePos)
{
    // If the selected child is active then give it events
	if (hasSelection() && mChildren[mSelectedChild]->isActive())
	{
		return mChildren[mSelectedChild]->handleInput(event, stdAc, mousePos);
	}
	else //else navigate through the container
    {
        //first, standard actions
        if(hasSelection())
        {
            switch(stdAc)
            {
            case IH::Up:
            case IH::Left:
                selectPrevious();
                return false;

            case IH::Down:
            case IH::Right:
                selectNext();
                return false;

            case IH::A:
                activateSelection();
                return false;
            }
        }
        //then, keyboard shortcuts
        if (event.type == sf::Event::KeyPressed)
        {
            for (int i(0); i < mChildren.size(); i++)
            {
                if (mChildren[i]->getShortcut() == event.key.code
                    and mChildren[i]->isSelectable()
                    and !mChildren[i]->isSelected())
                {
                    selectIndex(i);
                    activateSelection();
                    return false;
                }
            }
        }
        //then, mouse (part 1 : move)
        else if (event.type == sf::Event::MouseMoved)
        {
            for (int i(0); i < mChildren.size(); ++i)
            {
                if (mChildren[i]->contains(mousePos)
                    and !mChildren[i]->isSelected())
                    selectIndex(i);
            }
        }
        //then, mouse again (part 2 : clicks)
        else if(event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
        {
            for (int i(0); i < mChildren.size(); ++i)
            {
                if (mChildren[i]->contains(mousePos))
                {
                    selectIndex(i);
                    activateSelection();
                    return false;
                }
            }
        }
    }

    return true;
}

void Container::update(sf::Time delta)
{
    for (int i(0); i < mChildren.size(); ++i)
        mChildren[i]->update(delta);
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

	for(const Component::SPtr& child : mChildren)
		target.draw(*child, states);
}

bool Container::hasSelection() const
{
	return mSelectedChild >= 0;
}

void Container::selectIndex(std::size_t index)
{
	if (mChildren[index]->isSelectable()
        and !mChildren[index]->isSelected())
	{
		if (hasSelection())
			mChildren[mSelectedChild]->deselect();

		mChildren[index]->select();
		mSelectedChild = index;
	}
}

void Container::selectNext()
{
	if (!hasSelection())
		return;

	// Search next component that is selectable, wrap around if necessary
	int next = mSelectedChild;
	do
		next = (next + 1) % mChildren.size();
	while (!mChildren[next]->isSelectable());

	// Select that component
	selectIndex(next);
}

void Container::selectPrevious()
{
	if (!hasSelection())
		return;

	// Search previous component that is selectable, wrap around if necessary
	int prev = mSelectedChild;
	do
		prev = (prev + mChildren.size() - 1) % mChildren.size();
	while (!mChildren[prev]->isSelectable());

	// Select that component
	selectIndex(prev);
}

void Container::clear()
{
    mChildren.clear();
    mSelectedChild = -1;
}

}
