#ifndef UNITSELECT_HPP_INCLUDED
#define UNITSELECT_HPP_INCLUDED

#include "States/Arch/State.hpp"
#include "Gameplay/Battle/BattleContext.hpp"
#include "Graphism/Scene/EntityNode.hpp"

namespace States
{

class UnitSelect : public State
{
public:
    UnitSelect(StateStack* stack, Context context, BattleContext bc);
    ~UnitSelect();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);

private:
    BattleContext           mBattleContext;
    Graphism::EntityNode*   mNode;
};


}

#endif // UNITSELECT_HPP_INCLUDED
