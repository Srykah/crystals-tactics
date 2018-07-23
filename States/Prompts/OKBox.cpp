#include "States/Menu/OKBox.hpp"
#include "States/Arch/StateStack.hpp"
#include "Other/Utility.hpp"

namespace st
{

OKBox::OKBox(StateStack* stack, Context context, sf::String question, sf::String ok, sf::String back)
: State(stack, context)
, mQuestion(question, context.fonts->get(Fonts::Main))
, mOK(ok, context.fonts->get(Fonts::Main))
, mBack(back, context.fonts->get(Fonts::Main))
, mAButton(context.textures->get(Textures::XboxButtons))
, mBButton(context.textures->get(Textures::XboxButtons))
, mBackground(sf::Vector2f(1366.f, 768.f))
, mBox(sf::Vector2f(400.f, 300.f))
{
    mAButton.setTextureRect(sf::IntRect(0,0,36,36));
    mBButton.setTextureRect(sf::IntRect(36,0,60,60));
    mBackground.setFillColor(sf::Color(0,0,0,128));
    mBox.setFillColor(sf::Color::Blue);
    mBox.setOutlineThickness(5);
    mBox.setOutlineColor(sf::Color::White);

    centerOrigin(mQuestion);
    centerOrigin(mBox);
    centerOrigin(mAButton);
    centerOrigin(mOK);
    centerOrigin(mBButton);
    centerOrigin(mBack);

    mBox.setPosition(683.f, 384.f);
    mQuestion.setPosition(683.f, 264.f);
    mAButton.setPosition(613.f, 354.f);
    mOK.setPosition(733.f, 354.f);
    mBButton.setPosition(613.f, 384.f);
    mBack.setPosition(733.f, 404.f);
}

OKBox::~OKBox()
{

}

void OKBox::draw()
{
    sf::RenderWindow& window(*mContext.window);
    sf::View oldView(window.getView());
    window.setView(window.getDefaultView());

    window.draw(mBackground);
    window.draw(mBox);
    window.draw(mQuestion);
    window.draw(mAButton);
    window.draw(mOK);
    window.draw(mBButton);
    window.draw(mBack);

    window.setView(oldView);
}

bool OKBox::update(sf::Time dt)
{
    return true;
}

bool OKBox::handleEvent(const Input::Event& event)
{
    if (event.stdAc == Input::A)
        closeSuccess();
    else if (event.stdAc == Input::B)
        closeFailure();

    return false;
}

bool OKBox::handleSignal(const Signal& signal)
{
    return true;
}

}
