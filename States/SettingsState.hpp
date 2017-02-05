#ifndef SETTINGSSTATE_HPP_INCLUDED
#define SETTINGSSTATE_HPP_INCLUDED

#include "../StatesArch/State.hpp"
#include "../GUI/Container.hpp"

class SettingsState : public State
{
    public:
								SettingsState(StateStack& stack, State::Context context, const StateData& data);

		virtual void			draw();
		virtual bool			update(sf::Time dt);
		virtual bool			handleInput(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos);
		virtual States::ID      getID() const;

    private:
        GUI::Container          mContainer;
};

#endif // SETTINGSSTATE_HPP_INCLUDED
