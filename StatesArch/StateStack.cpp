#include "../StatesArch/StateStack.hpp"

#include <cassert>

StateStack::StateStack(State::Context context)
: mStack()
, mPendingList()
, mContext(context)
, mFactories()
{
}

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

void StateStack::handleInput(const sf::Event& event, IH::SA stdAc, sf::Vector2f mousePos)
{
	// Iterate from top to bottom, stop as soon as handleInput() returns false
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->handleInput(event, stdAc, mousePos))
			break;
	}

	applyPendingChanges();
}

void StateStack::pushState(States::ID stateID, const StateData& data, bool front)
{
    if (front)
        mPendingList.emplace_front(Push, nullptr, stateID, data);
    else
        mPendingList.emplace_back(Push, nullptr, stateID, data);
}

void StateStack::popState(bool front)
{
	if (front)
        mPendingList.emplace_front(Pop);
    else
        mPendingList.emplace_back(Pop);
}

void StateStack::closeState(State* ptr, bool front)
{
    if (front)
        mPendingList.emplace_front(Close, ptr);
    else
        mPendingList.emplace_back(Close, ptr);
}

void StateStack::closeTop(State* ptr, bool front)
{
    if (front)
        mPendingList.emplace_front(CloseTop, ptr);
    else
        mPendingList.emplace_back(CloseTop, ptr);
}

void StateStack::closeType(States::ID stateID, State* except, bool front)
{
    if (front)
        mPendingList.emplace_front(CloseType, except, stateID);
    else
        mPendingList.emplace_back(CloseType, except, stateID);
}

void StateStack::clearStates(bool front)
{
	if (front)
        mPendingList.emplace_front(Clear);
    else
        mPendingList.emplace_back(Clear);
}

bool StateStack::isEmpty() const
{
	return mStack.empty();
}

void StateStack::setData(States::ID stateID, const StateData& sd)
{
    mStateData[stateID] = sd;
}

const StateData& StateStack::getData(States::ID stateID)
{
    return mStateData[stateID];
}

State::Ptr StateStack::createState(States::ID stateID, const StateData& data)
{
	auto found = mFactories.find(stateID);
    assert(found != mFactories.end());

    return found->second(data);
}

void StateStack::applyPendingChanges()
{
	while(!mPendingList.empty())
	{
	    PendingChange change = mPendingList.front();
	    mPendingList.pop_front();

	    if (change.action == Push)
            mStack.push_back(createState(change.stateID, change.data));

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
        else if (change.action == CloseTop)
        {
            for (size_t i(0); i < mStack.size(); i++)
            {
                if (mStack[i].get() == change.ptr)
                {
                    mStack.erase(mStack.begin()+i+1, mStack.end());
                    break;
                }
            }
        }
        else if (change.action == CloseType)
        {
            for (size_t i(0); i < mStack.size(); i++)
            {
                if (mStack[i]->getID() == change.stateID and mStack[i].get() != change.ptr)
                {
                    mStack.erase(mStack.begin()+i);
                    i--;
                }
            }
        }
        else if (change.action == Clear)
            mStack.clear();
	}
}



StateStack::PendingChange::PendingChange(Action _action, State* ptr, States::ID _stateID, StateData _data)
: action(_action)
, ptr(ptr)
, stateID(_stateID)
, data(_data)
{

}
