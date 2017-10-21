#include "States/Editors/EntityEditor.hpp"

namespace States
{

EntityEditor::EntityEditor(StateStack* stack, Context context)
: State(stack, context)
{

}

void EntityEditor::draw()
{

}

bool EntityEditor::update(sf::Time dt)
{
    return false;
}

bool EntityEditor::handleEvent(const Input::Event& event)
{
    return false;
}

bool EntityEditor::handleSignal(const Signal& signal)
{
    return false;
}


}
