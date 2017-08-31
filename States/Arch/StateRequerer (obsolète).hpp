#ifndef STATEREQUERER_HPP_INCLUDED
#define STATEREQUERER_HPP_INCLUDED

#include <queue>
#include "States/StateIdentifiers.hpp"
#include "States/Arch/StateData.hpp"

/*//

Request

Cette structure sert pour qu'un �cran re�oive des requ�tes d'ouverture
ou de fermeture d'�cran la part d'objets qui ne peuvent pas modifier
directement la pile d'�crans de l'application.

Il est � la charge de l'�cran de v�rifier si un de ces objets a une requ�te
en r�serve.

//*/

namespace States
{

struct StateRequest
{
    enum Action
    {
        Push,
        Pop,
        Close,
        CloseTop,
        CloseType,
        CloseOthers,
        Clear,
        None
    };

    StateRequest(Action action = None, States::ID stateID = States::None, const StateData& data = StateData());

    Action action;
    States::ID stateID;
    const StateData& data;
};

/*//

StateRequerer

Cette classe de base sert pour tous les objets qui veulent interagir avec la
pile d'�crans. Cela permet aux �crans de r�cup�rer de mani�re universelle
les requ�tes de tels objets.

//*/

class StateRequerer
{
public:
    StateRequerer();
    virtual ~StateRequerer();

    bool hasStateRequest() const;
    int stateRequestCount() const;
    const StateRequest& getStateRequest();

protected:
    void addStateRequest(const StateRequest& sr);
    void clearStateRequests();

private:
    std::queue<StateRequest> mRequests;
};

}

#endif // STATEREQUERER_HPP_INCLUDED
