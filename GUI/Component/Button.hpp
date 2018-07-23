#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "GUI/Component.hpp"
#include "Data/ResourceHolder/ResourceIdentifiers.hpp"
#include "States/Arch/Context.hpp"
#include "Graphism/General/Text.hpp"
#include "Input/Listener.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <vector>
#include <SFML/System/String.hpp>
#include <memory>
#include <functional>

namespace GUI
{

class Button : public Component
{
    public:
        typedef std::shared_ptr<Button>		SPtr;
        typedef std::function<void()>		Callback;

		enum Mode
		{
			Normal,
			Selected,
			Pressed,
			ButtonCount
		};

		enum Type
		{
		    Menu,
		    Settings,
		    UpArrow,
		    DownArrow,
		    LeftArrow,
		    RightArrow,
		    CloseDialog,
		    MoveDialog
		};


	public:
                                    Button(sa::Context context, Type type);

        void					    setCallback(Callback callback);
        void					    setText(const sf::String& text);
        void					    setManualDeactivation(bool flag);

        virtual bool			    isSelectable() const;
        virtual void			    select();
        virtual void			    deselect();

        virtual void		    	activate();
        virtual void		    	deactivate();

        void                        stayPressed(bool flag);
        void                        unpress();

        virtual bool                contains(sf::Vector2f point) const;
        virtual bool                contains(float x, float y) const;

        virtual bool		    	handleEvent(const Input::Event& event);
        virtual void                update(sf::Time delta);


    private:
        virtual void		    	draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void				    	changeTexture(Mode buttonMode);


    private:
        Type                        mType;
        Callback			    	mCallback;
        sf::Sprite			    	mSprite;
        gr::Text			    mText;
        bool				    	mManualDeactivation;
        bool                        mStayPressed;
};

}

#endif // BUTTON_HPP_INCLUDED
