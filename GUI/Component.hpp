#ifndef COMPONENT_HPP_INCLUDED
#define COMPONENT_HPP_INCLUDED

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>

#include <memory>

#include "Input/Listener.hpp"


namespace sf
{
	class Event;
}

namespace GUI
{

class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
    public:
        typedef std::shared_ptr<Component> SPtr;


	public:
                                    Component();
        virtual				        ~Component();

        virtual bool		        isSelectable() const = 0;
		bool				        isSelected() const;
        virtual void		        select();
        virtual void		        deselect();
        virtual void                setShortcut(sf::Keyboard::Key shortcut);
        virtual sf::Keyboard::Key   getShortcut() const;

        virtual bool		        isActive() const;
        virtual void		        activate();
        virtual void		        deactivate();

        virtual bool                contains(sf::Vector2f point) const = 0;
        virtual bool                contains(float x, float y) const = 0;

        virtual bool	        	handleEvent(const Input::Event& event) = 0;
        virtual void                update(sf::Time delta) = 0;


    private:
        bool			        	mIsSelected;
        bool			        	mIsActive;

    protected:
		sf::Keyboard::Key           mShortcut;
};

}

#endif // COMPONENT_HPP_INCLUDED
