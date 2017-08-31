#ifndef STATESTACK_HPP_INCLUDED
#define STATESTACK_HPP_INCLUDED

#include "States/Arch/State.hpp"
#include "Data/ResourceHolder/ResourceIdentifiers.hpp"
#include "Input/Listener.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <deque>

namespace States
{

class StateStack : private sf::NonCopyable
{
public:
    enum Action
    {
        Push,
        Pop,
        Close,
        Clear
    };

public:
    void				update(sf::Time dt);
    void				draw();
    void				handleEvent(const Input::Event& event);
    void                handleSignal();

    void				push(State* state, bool front = false);
    void				pop(bool front = false);
    void                close(State* state, bool front = false);
    void				clear(bool front = false);

    void                addSignal(State* state, Signal::Data& data);

    bool				isEmpty() const;

private:
    void				applyPendingChanges();

private:
    struct PendingChange
    {
        explicit	    PendingChange(Action action, State* ptr = nullptr) :
            action(action), ptr(ptr) {}

        Action			action;
        State*          ptr;
    };

private:
    std::vector<State::Ptr>		mStack;
    std::deque<PendingChange>	mPendingList;
    std::queue<Signal>          mSignals;
};

}

#endif // STATESTACK_HPP_INCLUDED
