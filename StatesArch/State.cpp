#include "../StatesArch/State.hpp"
#include "../StatesArch/StateStack.hpp"

/*//

Source de la classe State

//*/

/*//

Constructeur : il ne fait qu'initialiser ses deux membres avec les paramètres fournis.

//*/
State::State(StateStack& stack, State::Context context)
: mStack(&stack)
, mContext(context)
{
}

State::~State()
{
}

/*//

Classes de requête (interne) : elles se contentent d'appeler la fonction correspondante de mStack.

//*/

void State::requestStackPush(States::ID stateID, const StateData& data, bool front)
{
	mStack->pushState(stateID, data, front);
}

void State::requestStackPop(bool front)
{
	mStack->popState(front);
}

void State::requestStackClose(bool front)
{
    mStack->closeState(this, front);
}

void State::requestStackCloseTop(bool front)
{
    mStack->closeTop(this, front);
}

void State::requestStackCloseType(States::ID stateID, bool front)
{
    mStack->closeType(stateID, nullptr, front);
}

void State::requestStackCloseOthers(bool front)
{
    mStack->closeType(getID(), this, front);
}

void State::requestStackClear(bool front)
{
	mStack->clearStates(front);
}

/*//

Cette fonction appelle une des trois ci-dessus en fonction du type de requête.

//*/

void State::requestStackAction(StateRequest req, bool front)
{
    switch (req.action)
    {
    case StateRequest::Clear:
        requestStackClear(front);
        break;

    case StateRequest::Pop:
        requestStackPop(front);
        break;

    case StateRequest::Close:
        requestStackClose(front);
        break;

    case StateRequest::CloseTop:
        requestStackCloseTop(front);
        break;

    case StateRequest::CloseType:
        requestStackCloseType(req.stateID, front);
        break;

    case StateRequest::CloseOthers:
        requestStackCloseOthers(front);

    case StateRequest::Push:
        requestStackPush(req.stateID, req.data, front);

    default:;
    }
}

State::Context State::getContext() const
{
	return mContext;
}

void State::setData(const StateData& sd)
{
    mStack->setData(getID(), sd);
}

const StateData& State::getData(States::ID stateID) const
{
    return mStack->getData(stateID);
}

/*//

Sources de la structure Context

Constructeur : initialise les membres à partir des paramètres.

//*/

State::Context::Context(sf::RenderWindow& window,
                        IH& inputHandler,
                        TextureHolder& textures, FontHolder& fonts,
                        MusicPlayer& music, SoundPlayer& sounds,
                        EntityHolder& entities,
                        Data::StatsData& stats, Data::ItemsData& items, Data::AbsData& abilities,
                        Guild& guild)
: window(&window)
, inputHandler(&inputHandler)
, textures(&textures), fonts(&fonts)
, music(&music), sounds(&sounds)
, entities(&entities)
, stats(&stats), items(&items), abilities(&abilities)
, guild(&guild)
{

}
