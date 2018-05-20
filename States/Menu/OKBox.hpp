#ifndef OKBOX_HPP_INCLUDED
#define OKBOX_HPP_INCLUDED

#include "States/Arch/State.hpp"

#include <SFML/System/String.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Graphism/Text.hpp"

namespace st
{

class OKBox : public State
{
public:
    OKBox(StateStack* stack, Context context, sf::String question, sf::String ok="OK", sf::String back="Retour");
    ~OKBox();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);

private:
    gr::Text      mQuestion, mOK, mBack;
    sf::Sprite          mAButton, mBButton;
    sf::RectangleShape  mBackground, mBox;
};


}

#endif // OKBOX_HPP_INCLUDED
