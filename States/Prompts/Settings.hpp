#ifndef SETTINGSSTATE_HPP_INCLUDED
#define SETTINGSSTATE_HPP_INCLUDED

#include "States/Arch/State.hpp"
#include "GUI/Container.hpp"

namespace st
{

class Settings : public State
{
    public:
								Settings(StateStack* stack, Context context);

		virtual void			draw();
		virtual bool			update(sf::Time dt);
		virtual bool			handleEvent(const Input::Event& event);
        virtual bool            handleSignal(const Signal& signal);

    private:
        GUI::Container          mContainer;
};

}

#endif // SETTINGSSTATE_HPP_INCLUDED
