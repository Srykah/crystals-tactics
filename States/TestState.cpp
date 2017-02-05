#include "../States/TestState.hpp"

TestState::TestState(StateStack& stack, State::Context& context, const StateData& data)
: State(stack, context)
, mMenu(context.fonts->get(Fonts::Main))
, mText("", context.fonts->get(Fonts::Main))
{
    mMenu.addEntry(GUI::BattleMenu::Entry("1", 1));
    mMenu.addEntry(GUI::BattleMenu::Entry("2", 2, true));
    mMenu.addEntry(GUI::BattleMenu::Entry("3", 3));

    mMenu.setPosition(400,300);
    mText.setPosition(800, 350);
}

TestState::~TestState()
{

}

void TestState::draw()
{
    sf::RenderWindow& window(*getContext().window);

    window.draw(mMenu);
    window.draw(mText);
}

bool TestState::update(sf::Time dt)
{
    if (mMenu.hasResult())
    {
        int res(mMenu.getResult());

        if (res == 1)
            mText.setString("1");
        else if (res == 2)
            mText.setString("2");
        else if (res == 3)
            mText.setString("3");
    }

    return false;
}

bool TestState::handleInput(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos)
{
    mMenu.handleInput(event, stdAction, mousePos);

    return false;
}

States::ID TestState::getID() const
{
    return States::Test;
}
