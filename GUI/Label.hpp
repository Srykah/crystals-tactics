#ifndef BOOK_LABEL_HPP
#define BOOK_LABEL_HPP

#include "../GUI/Component.hpp"
#include "../Other/ResourceIdentifiers.hpp"
#include "../Other/ResourceHolder.hpp"
#include "../Graphism/Text.hpp"

namespace GUI
{

class Label : public Component
{
    public:
        typedef std::shared_ptr<Label> SPtr;


	public:
							Label(const std::string& text, const FontHolder& fonts);

        virtual bool		isSelectable() const;
		void				setText(const std::string& text);

		virtual bool        contains(sf::Vector2f point) const;
		virtual bool        contains(float x, float y) const;

        virtual bool		handleInput(const sf::Event& event, IH::SA stdAc, sf::Vector2f mousePos);
        virtual void        update(sf::Time delta);



    private:
        void				draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        Graphism::Text		mText;
};

}

#endif // BOOK_LABEL_HPP
