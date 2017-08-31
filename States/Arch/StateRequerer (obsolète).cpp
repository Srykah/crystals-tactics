#include "States/Arch/StateRequerer.hpp"

/*//

Sources de la structure StateRequest

//*/

namespace States
{

/*//

Constructeur : initialise les membres � partir des param�tres.

//*/

StateRequest::StateRequest(Action action, States::ID stateID, const StateData& data)
: action(action)
, stateID(stateID)
, data(data)
{

}

/*//

Sources de la classe StateRequerer

Constructeur et destructeur vides (la file se g�re toute seule)

//*/

StateRequerer::StateRequerer()
{

}

StateRequerer::~StateRequerer()
{

}

bool StateRequerer::hasStateRequest() const
{
    return !mRequests.empty();
}

int StateRequerer::stateRequestCount() const
{
    return mRequests.size();
}

const StateRequest& StateRequerer::getStateRequest()
{
    const StateRequest& sr = mRequests.front();
    mRequests.pop();
    return sr;
}

void StateRequerer::addStateRequest(const StateRequest& sr)
{
    mRequests.push(sr);
}

void StateRequerer::clearStateRequests()
{
    while(hasStateRequest())
        mRequests.pop();
}

}
