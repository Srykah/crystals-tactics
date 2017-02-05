#ifndef BOOK_PAUSESTATE_HPP
#define BOOK_PAUSESTATE_HPP

#include "../StatesArch/State.hpp"
#include "../GUI/Container.hpp"
#include "../Graphism/Text.hpp"

#include <SFML/Graphics/Sprite.hpp>


class PauseState : public State
{
	public:
							PauseState(StateStack& stack, State::Context context, const StateData& data);
							~PauseState();

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleInput(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos);
        virtual States::ID  getID() const;

	private:
		sf::Sprite			mBackgroundSprite;
		Graphism::Text		mPausedText;
		GUI::Container 		mGUIContainer;
};

#endif // BOOK_PAUSESTATE_HPP
