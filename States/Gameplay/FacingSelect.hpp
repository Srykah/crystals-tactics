#ifndef FACINGSELECT_HPP_INCLUDED
#define FACINGSELECT_HPP_INCLUDED

#include "States/Gameplay/BattleState.hpp"
#include "Graphism/Scene/EmptyNode.hpp"
#include "Gameplay/Battle/BattleContext.hpp"

class Character;

namespace st
{

class FacingSelect : public BattleState
{
public:
    FacingSelect(StateStack* stack, Context context, BattleContext bc, Character& unit, bool cancellable = false);
    ~FacingSelect() = default;

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);

private:
    gr::EmptyNode*          mNode;
    Character&              mUnit;
    const Direction::Dir    mInitialFacing;
    const bool              mCancellable;
};

}

#endif // FACINGSELECT_HPP_INCLUDED
