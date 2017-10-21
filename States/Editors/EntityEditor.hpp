#ifndef ENTITYEDITOR_HPP_INCLUDED
#define ENTITYEDITOR_HPP_INCLUDED

#include "States/Arch/State.hpp"
#include "Graphism/Text.hpp"
#include "GUI/Container.hpp"

namespace States
{

class EntityEditor : public State
{
public:
    EntityEditor(StateStack* stack, Context context);

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);

private:
    GUI::Container      mContainer;
    sf::RectangleShape	mBackground;
    sf::Sprite          mSpriteSheet;
    //Graphism::Text	    mText;
};

}

#endif // ENTITYEDITOR_HPP_INCLUDED
