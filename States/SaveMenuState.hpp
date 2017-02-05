#ifndef SAVEMENU_HPP_INCLUDED
#define SAVEMENU_HPP_INCLUDED

#include "../StatesArch/State.hpp"
#include <SFML/Graphics/Text.hpp>
#include "../GUI/Container.hpp"
#include "../Graphism/Text.hpp"

class SaveMenuState : public State
{
public:
    SaveMenuState(StateStack& stack, State::Context& context, const StateData& data);
    ~SaveMenuState();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleInput(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos);
    virtual States::ID  getID() const;

private:
    GUI::Container mContainer;
    Graphism::Text mMessage;
    int mSelection;
    bool mLoadingMode;
    bool mConfirmed;
    sf::VertexArray mBackground;
};

#endif // SAVEMENU_HPP_INCLUDED
