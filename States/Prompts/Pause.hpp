#ifndef PAUSESTATE_HPP_INCLUDED
#define PAUSESTATE_HPP_INCLUDED

#include "States/Arch/State.hpp"
#include "GUI/Container.hpp"
#include "Graphism/General/Text.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace st
{

class Pause : public State
{
public:
    Pause(StateStack* stack, Context context);
    ~Pause();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);

private:
    sf::Sprite			mBackgroundSprite;
    gr::Text		mPausedText;
    GUI::Container 		mGUIContainer;
};

}

#endif // PAUSESTATE_HPP_INCLUDED
