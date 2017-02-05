#ifndef BOOK_ANIMATION_HPP
#define BOOK_ANIMATION_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include <memory>
#include <vector>

namespace Graphism
{

namespace Animations
{
    enum Type
    {
        Idle,
        Moving,
        MeleeAttack,
        RangeAttack,
        BareFistAttack,
        None
    };
}

class Animation : public sf::Drawable
{
	public:
	    struct Frame
	    {
	        Frame(sf::IntRect textureRect, sf::Vector2f origin);
	        ~Frame();

	        sf::IntRect textureRect;
	        sf::Vector2f origin;
	    };

	    typedef std::shared_ptr<Animation> SPtr;

								Animation();
		explicit 				Animation(const sf::Texture* texture);

		void 					setTexture(const sf::Texture* texture);
		const sf::Texture* 		getTexture() const;

		void                    addFrame(Frame frame);
		std::size_t             getNumFrames() const;

		void 					setDuration(sf::Time duration);
		sf::Time 				getDuration() const;

		void 					setRepeating(bool flag);
		bool 					isRepeating() const;

		void 					restart();
		bool 					isFinished() const;

		sf::FloatRect 			getLocalBounds() const;

		void 					update(sf::Time dt);


	private:
		void 					draw(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		sf::Sprite 		    mSprite;
		std::vector<Frame>  mFrames;
		std::size_t 		mCurrentFrame;
		sf::Time            mDuration;
		sf::Time            mElapsedTime;
		bool                mRepeat;
};

}

Graphism::Animations::Type stringToAT(std::string str);

#endif // BOOK_ANIMATION_HPP
