#ifndef CHARACINFO_HPP_INCLUDED
#define CHARACINFO_HPP_INCLUDED

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../GUI/Container.hpp"
#include "../Graphism/Text.hpp"
#include "../Graphism/RatioBar.hpp"
#include "../Gameplay/Character.hpp"
#include "../StatesArch/State.hpp"

namespace Graphism
{

class CharacInfo : public sf::Drawable, public sf::Transformable
{
public:
    CharacInfo(State::Context context, Character* charac = nullptr);
    ~CharacInfo();

    void		draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;
    void		update(sf::Time dt);
    void		handleInput(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos);

    void        setCharacter(Character* charac);

private:
    enum Style
    {
        Minimal,
        Full
    };

    void placeThings();
    void fillTexts();

    sf::RectangleShape  mBackground;
    Character*     mCharacter;

    Stats               mStatsCache;
    Stat                mLvlCache;
    Stat                mHPCache;
    Stat                mSpdCntCache;

    sf::RectangleShape  mFace;
    Graphism::Text      mNameText;
    Graphism::Text      mJobText;
    Graphism::Text      mLevelText;
    Graphism::Text      mHPText;
    Graphism::RatioBar  mHPBar;
    Graphism::Text      mSpdCntText;
    Graphism::Text      mAtkText;
    Graphism::Text      mDefText;
    Graphism::Text      mMobText;
    Graphism::Text      mEvadeText;
    Graphism::Text      mSpeedText;

};

}

#endif // CHARACINFO_HPP_INCLUDED
