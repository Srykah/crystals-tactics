#include "States/Editors/EditorsMenu.hpp"
#include "GUI/Button.hpp"
#include "States/Arch/StateStack.hpp"
#include "States/Menu/Title.hpp"
#include "States/Editors/EntityEditor.hpp"

namespace States
{

EditorsMenu::EditorsMenu(StateStack* stack, Context context)
: State(stack, context)
, mBackground(sf::Vector2f(1366, 768))
{
    mBackground.setFillColor(sf::Color(0,0,32));

    auto entityButton = std::make_shared<GUI::Button>(context, GUI::Button::Menu);
	entityButton->setPosition(100, 350);
	entityButton->setText("Éditeur d'entités graphiques");
	entityButton->setCallback([this] ()
	{
		mStack->clear();
		mStack->push(new EntityEditor(mStack, mContext));
	});

    auto returnButton = std::make_shared<GUI::Button>(context, GUI::Button::Menu);
	returnButton->setPosition(100, 550);
	returnButton->setText("Retour");
	returnButton->setCallback([this] ()
	{
		mStack->clear();
		mStack->push(new Title(mStack, mContext));
	});

	mMenu.pack(entityButton);
	mMenu.pack(returnButton);
}

void EditorsMenu::draw()
{
    mContext.window->draw(mBackground);
    mContext.window->draw(mMenu);
}

bool EditorsMenu::update(sf::Time dt)
{
    mMenu.update(dt);

    return false;
}

bool EditorsMenu::handleEvent(const Input::Event& event)
{
    mMenu.handleEvent(event);

    return false;
}

bool EditorsMenu::handleSignal(const Signal& signal)
{
    return false;
}


}
