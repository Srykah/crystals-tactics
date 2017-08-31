#ifndef SAVEMENU_HPP_INCLUDED
#define SAVEMENU_HPP_INCLUDED

#include "States/Arch/State.hpp"
#include <SFML/Graphics/Text.hpp>
#include "GUI/Container.hpp"
#include "Graphism/Text.hpp"

namespace States
{

class SaveMenu : public State
{
public:
    SaveMenu(StateStack* stack, Context context, bool loading = false);
    ~SaveMenu();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);

private:
    GUI::Container mContainer;
    Graphism::Text mMessage;
    int mSelection;
    bool mLoadingMode;
    bool mConfirmed;
    sf::VertexArray mBackground;
};

}

#endif // SAVEMENU_HPP_INCLUDED
