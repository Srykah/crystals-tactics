#ifndef BOOK_BUTTON_HPP
#define BOOK_BUTTON_HPP

#include "../GUI/Component.hpp"
#include "../Other/ResourceIdentifiers.hpp"
#include "../StatesArch/State.hpp"
#include "../Graphism/Text.hpp"
#include "../Input/InputHandler.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <vector>
#include <string>
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
                                    Button(State::Context context, Type type);

        void					    setCallback(Callback callback);
        void					    setText(const std::string& text);
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

        virtual bool		    	handleInput(const sf::Event& event, IH::SA stdAc, sf::Vector2f mousePos);
        virtual void                update(sf::Time delta);


    private:
        virtual void		    	draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void				    	changeTexture(Mode buttonMode);


    private:
        Type                        mType;
        Callback			    	mCallback;
        sf::Sprite			    	mSprite;
        Graphism::Text			    mText;
        bool				    	mManualDeactivation;
        bool                        mStayPressed;
};

}

#endif // BOOK_BUTTON_HPP
