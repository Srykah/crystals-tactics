#ifndef LABEL_HPP_INCLUDED
#define LABEL_HPP_INCLUDED

#include "GUI/Component.hpp"
#include "Data/ResourceHolder/ResourceIdentifiers.hpp"
#include "Data/ResourceHolder/ResourceHolder.hpp"
#include "Graphism/Text.hpp"

namespace GUI
{

class Label : public Component
{
    public:
        typedef std::shared_ptr<Label> SPtr;


	public:
							Label(const sf::String& text, const Data::FontHolder& fonts);

        virtual bool		isSelectable() const;
		void				setText(const sf::String& text);

		virtual bool        contains(sf::Vector2f point) const;
		virtual bool        contains(float x, float y) const;

        virtual bool		handleEvent(const Input::Event& event);
        virtual void        update(sf::Time delta);



    private:
        void				draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        Graphism::Text		mText;
};

}

#endif // LABEL_HPP_INCLUDED
