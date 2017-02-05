#ifndef ICONBUTTON_HPP_INCLUDED
#define ICONBUTTON_HPP_INCLUDED

#include "../GUI/Component.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <memory>
#include <functional>

namespace GUI
{

class IconButton : public Component
{
public:
    typedef std::shared_ptr<IconButton>		SPtr;
    typedef std::function<void()>		Callback;

    enum Mode
    {
        Normal,
        Selected,
        Pressed
    };

                                IconButton(const sf::Texture& tex, bool selectable = true);
                                ~IconButton();

    void					    setCallback(Callback callback);

    virtual bool			    isSelectable() const;
    void                        setSelectable(bool flag = true);
    virtual void			    select();
    virtual void			    deselect();

    virtual void		    	activate();
    virtual void		    	deactivate();

    virtual bool                contains(sf::Vector2f point) const;
    virtual bool                contains(float x, float y) const;

    virtual bool		    	handleInput(const sf::Event& event, IH::SA stdAc, sf::Vector2f mousePos);
    virtual void                update(sf::Time delta);


private:
    virtual void		    	draw(sf::RenderTarget& target, sf::RenderStates states) const;

    bool                        mIsSelectable;
    Callback			    	mCallback;
    sf::Sprite			    	mSprite;
};

}

#endif // ICONBUTTON_HPP_INCLUDED
