#ifndef UNITSELECT_HPP_INCLUDED
#define UNITSELECT_HPP_INCLUDED

#include "States/Gameplay/BattleState.hpp"
#include "Gameplay/Battle/BattleContext.hpp"
#include "Graphism/Scene/EntityNode.hpp"
#include "Graphism/HUD/CharacInfo.hpp"
#include "States/Gameplay/FacingSelect.hpp"

namespace st
{

class UnitSelect : public BattleState
{
public:
    UnitSelect(StateStack* stack, Context context, bt::BattleContext bc);
    ~UnitSelect();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);

private:
    void                changeCharacter(short offset);

private:
    short               mIndex;
    gr::CharacInfo      mCharacInfo;
    gr::EntityNode*     mNode;
    st::FacingSelect*   mChildState;
};


}

#endif // UNITSELECT_HPP_INCLUDED
