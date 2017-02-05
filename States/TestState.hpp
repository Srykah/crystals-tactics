#ifndef TESTSTATE_HPP_INCLUDED
#define TESTSTATE_HPP_INCLUDED

#include "../StatesArch/State.hpp"
#include "../States/TestState.hpp"
#include "../GUI/BattleMenu.hpp"
#include "../Graphism/Text.hpp"

class TestState : public State
{
public:
    TestState(StateStack& stack, State::Context& context, const StateData& data);
    ~TestState();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleInput(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos);
    virtual States::ID  getID() const;

private:
    GUI::BattleMenu     mMenu;
    Graphism::Text      mText;
};

#endif // TESTSTATE_HPP_INCLUDED
