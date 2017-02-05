#ifndef BOOK_CONTAINER_HPP
#define BOOK_CONTAINER_HPP

#include "../GUI/Component.hpp"
#include "../Input/InputHandler.hpp"

#include <vector>
#include <memory>

namespace GUI
{

class Container : public Component
{
    public:
        typedef std::shared_ptr<Container> SPtr;

	public:
                                    Container();

        void				        pack(Component::SPtr component);
        void				        selectIndex(std::size_t index);
        int                         getSelectionIndex() const;
        void                        activateSelection();

        virtual bool                contains(sf::Vector2f point) const;
        virtual bool                contains(float x, float y) const;

        virtual bool		        isSelectable() const;

        virtual bool		        handleInput(const sf::Event& event, IH::SA stdAc, sf::Vector2f mousePos);
        virtual void                update(sf::Time delta);

    private:
        virtual void		        draw(sf::RenderTarget& target, sf::RenderStates states) const;

        bool				        hasSelection() const;
        void				        selectNext();
        void				        selectPrevious();

        void                        clear();


    private:
        std::vector<Component::SPtr>	mChildren;
        int								mSelectedChild;
};

}

#endif // BOOK_CONTAINER_HPP
