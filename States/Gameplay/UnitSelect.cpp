#include "States/Gameplay/UnitSelect.hpp"
#include "Gameplay/Story/Guild.hpp"
#include "Data/ResourceHolder/ResourceIdentifiers.hpp"
#include "Graphism/HUD/Cursor.hpp"

namespace States
{

UnitSelect::UnitSelect(StateStack* stack, Context context, BattleContext bc)
: State(stack, context)
, mBattleContext(bc)
, mNode(
    new Graphism::EntityNode(
        new Graphism::Entity(
            context.entities->get(
                CharTypeToEntitiesID(
                    context.guild->getMember(0)->getType()
                )
            ),
            "idle",
            Direction::Down
        ),
        bc.cursor->getCoords().y
    )
)
{
    bc.scene->addNode(mNode);
}

UnitSelect::~UnitSelect()
{

}

void UnitSelect::draw()
{

}

bool UnitSelect::update(sf::Time dt)
{
    return true;
}

bool UnitSelect::handleEvent(const Input::Event& event)
{
    return true;
}

bool UnitSelect::handleSignal(const Signal& signal)
{
    return true;
}


}
