#include "States/Arch/State.hpp"
#include "States/Arch/StateStack.hpp"

/*//

Source de la classe State

//*/

namespace st
{

/*//
Constructeur : il ne fait qu'initialiser ses deux membres avec les paramètres fournis.
//*/

State::State(StateStack* stack, Context context)
: mStack(stack)
, mContext(context)
{
}

State::~State()
{
}

void State::emit(Signal::Data data)
{
    mStack->addSignal(this, data);
}

void State::closeSuccess()
{
    emit(true);
    mStack->close(this);
}

void State::closeFailure()
{
    emit(false);
    mStack->close(this);
}

}
