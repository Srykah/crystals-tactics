#include "States/Arch/StateStack.hpp"

#include <cassert>

namespace States
{

void StateStack::update(sf::Time dt)
{
	// Iterate from top to bottom, stop as soon as update() returns false
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->update(dt))
			break;
	}

	applyPendingChanges();
}

void StateStack::draw()
{
	// Draw all active states from bottom to top
	for(State::Ptr& state : mStack)
		state->draw();
}

void StateStack::handleEvent(const Input::Event& event)
{
	// Iterate from top to bottom, stop as soon as handleEvent() returns false
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->handleEvent(event))
			break;
	}

	applyPendingChanges();
}

void StateStack::handleSignal()
{
    while (!mSignals.empty())
    {
        Signal signal(mSignals.front());
        mSignals.pop();
        // Iterate from top to bottom, stop as soon as handleSignal() returns false
        for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
        {
            if (!(*itr)->handleSignal(signal))
                break;
        }
    }

	applyPendingChanges();
}

void StateStack::push(State* state)
{
    mPendingList.emplace(Push, state);
}

void StateStack::pop()
{
    mPendingList.emplace(Pop);
}

void StateStack::close(State* ptr)
{
    mPendingList.emplace(Close, ptr);
}

void StateStack::clear()
{
    mPendingList.emplace(Clear);
}

bool StateStack::isEmpty() const
{
	return mStack.empty();
}

void StateStack::applyPendingChanges()
{
	while(!mPendingList.empty())
	{
	    PendingChange change = mPendingList.front();
	    mPendingList.pop();

	    if (change.action == Push)
            mStack.emplace_back(change.ptr);

        else if (change.action == Pop)
            mStack.pop_back();

        else if (change.action == Close)
        {
            for (size_t i(0); i < mStack.size(); i++)
            {
                if (mStack[i].get() == change.ptr)
                {
                    mStack.erase(mStack.begin()+i);
                    break;
                }
            }
        }

        else if (change.action == Clear)
            mStack.clear();
	}
}

void StateStack::addSignal(State* state, Signal::Data& data)
{
    mSignals.emplace(state, data);
}

}