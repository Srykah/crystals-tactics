#ifndef BOOK_TITLESTATE_HPP
#define BOOK_TITLESTATE_HPP

#include "../StatesArch/State.hpp"
#include "../Graphism/Text.hpp"
#include "../GUI/Container.hpp"

#include <SFML/Graphics/Sprite.hpp>


class TitleState : public State
{
	public:
							TitleState(StateStack& stack, State::Context context, const StateData& data);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleInput(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos);
        virtual States::ID  getID() const;

	private:
	    TextureHolder       mTextures;
	    GUI::Container      mMenu;
	    sf::Sprite          mTNTeamSprite;
		sf::Sprite			mBackgroundSprite;
		sf::Sprite          mCTSprite;
		Graphism::Text	    mContinueText;
		sf::Time			mEffectTime;
		int                 mPhase;
};

#endif // BOOK_TITLESTATE_HPP
