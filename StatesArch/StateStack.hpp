#ifndef BOOK_STATESTACK_HPP
#define BOOK_STATESTACK_HPP

#include "../StatesArch/State.hpp"
#include "../States/StateIdentifiers.hpp"
#include "../Other/ResourceIdentifiers.hpp"
#include "../Input/InputHandler.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <deque>
#include <utility>
#include <functional>
#include <map>
#include <memory>


namespace sf
{
	class Event;
	class RenderTexture;
}

class State;

class StateStack : private sf::NonCopyable
{
	public:
		enum Action
		{
			Push,
			Pop,
			Close,
			CloseTop,
			CloseType,
			Clear
		};


	public:
		explicit			StateStack(State::Context context);

        template <typename T>
		void				registerState(States::ID stateID);

		void				update(sf::Time dt);
		void				draw();
		void				handleInput(const sf::Event& event, IH::SA stdAc, sf::Vector2f mousePos);

		void				pushState(States::ID stateID, const StateData& data = StateData(), bool front = false);
		void				popState(bool front = false);
		void                closeState(State* state, bool front = false);
		void                closeTop(State* state, bool front = false);
		void                closeType(States::ID stateID, State* except = nullptr, bool front = false);
		void				clearStates(bool front = false);

		bool				isEmpty() const;

		void                setData(States::ID stateID, const StateData& sd);
		const StateData&    getData(States::ID stateID);

	private:
	    State::Ptr			createState(States::ID stateID, const StateData& data);
		void				applyPendingChanges();


	private:
		struct PendingChange
		{
		    explicit			PendingChange(Action action, State* ptr = nullptr, States::ID stateID = States::None, StateData = StateData());

			Action				action;
			State*              ptr;
			States::ID			stateID;
			StateData           data;
		};

	private:
		std::vector<State::Ptr>		                    mStack;
		std::deque<PendingChange>					        mPendingList;


		State::Context										mContext;
		std::map<States::ID,
                 std::function<State::Ptr(StateData)>>	    mFactories;
        std::map<States::ID, StateData>                     mStateData;
};

#include "StateStack.inl"

#endif // BOOK_STATESTACK_HPP
