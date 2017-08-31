
template <typename T>
void StateStack::registerState(States::ID stateID)
{
	mFactories[stateID] = [this] (const StateData& data)
	{
		return State::Ptr(new T(*this, mContext, data));
	};
}
