#ifndef EDITORSMENU_HPP_INCLUDED
#define EDITORSMENU_HPP_INCLUDED

#include "States/Arch/State.hpp"
#include "GUI/Container.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace States
{

class EditorsMenu : public State
{
public:
    EditorsMenu(StateStack* stack, Context context);

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);

private:
    GUI::Container      mMenu;
    sf::RectangleShape	mBackground;
};

}

#endif // EDITORSMENU_HPP_INCLUDED
