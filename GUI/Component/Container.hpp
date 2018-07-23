#ifndef CONTAINER_HPP_INCLUDED
#define CONTAINER_HPP_INCLUDED

#include "GUI/Component.hpp"
#include "Input/Listener.hpp"

#include <vector>
#include <memory>

namespace GUI
{

class Container : public Component
{
    public:
        typedef std::shared_ptr<Container> SPtr;
        static const char VERTICAL = 1;
        static const char HORIZONTAL = 2;
        static const char DEFAULT = 3;

	public:
                                    Container(char scrollDirection = DEFAULT);

        void				        pack(Component::SPtr component);
        void				        selectIndex(std::size_t index);
        int                         getSelectionIndex() const;
        void                        activateSelection();

        virtual bool                contains(sf::Vector2f point) const;
        virtual bool                contains(float x, float y) const;

        virtual bool		        isSelectable() const;

        virtual bool		        handleEvent(const Input::Event& event);
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
        char                            mScrollDirection;
};

}

#endif // CONTAINER_HPP_INCLUDED
