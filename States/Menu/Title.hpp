#ifndef TITLESTATE_HPP_INCLUDED
#define TITLESTATE_HPP_INCLUDED

#include "States/Arch/State.hpp"
#include "Graphism/Text.hpp"
#include "GUI/Container.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace st
{

class Title : public State
{
public:
    Title(StateStack* stack, Context context);

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);

private:
    Data::TextureHolder       mTextures;
    GUI::Container      mMenu;
    sf::Sprite          mTNTeamSprite;
    sf::Sprite			mBackgroundSprite;
    sf::Sprite          mCTSprite;
    gr::Text	    mContinueText;
    sf::Time			mEffectTime;
    int                 mPhase;
};

}

#endif // TITLESTATE_HPP_INCLUDED
