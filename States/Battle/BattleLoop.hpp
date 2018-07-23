#ifndef BATTLELOOP_HPP_INCLUDED
#define BATTLELOOP_HPP_INCLUDED

#include "States/Battle/BattleState.hpp"

namespace bs
{

class BattleLoop : public BattleState
{
public:
    BattleLoop(sa::StateStack*, sa::Context, bt::BattleContext);
    ~BattleLoop() = default;

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);
};

}

#endif // BATTLELOOP_HPP_INCLUDED
