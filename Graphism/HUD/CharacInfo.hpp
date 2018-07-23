#ifndef CHARACINFO_HPP_INCLUDED
#define CHARACINFO_HPP_INCLUDED

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "GUI/Container.hpp"
#include "Graphism/General/Text.hpp"
#include "Graphism/HUD/RatioBar.hpp"
#include "Gameplay/Character/Character.hpp"
#include "States/Arch/Context.hpp"

namespace gr
{

class CharacInfo : public sf::Drawable, public sf::Transformable
{
public:
    CharacInfo(sa::Context context, Character* charac = nullptr);
    ~CharacInfo();

    void		draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;
    void		update(sf::Time dt);
    void		handleEvent(const Input::Event& event);

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
    Character*          mCharacter;

    Stats               mStatsCache;
    Stat                mLvlCache;
    Stat                mHPCache;
    Stat                mSpdCntCache;

    sf::RectangleShape  mFace;
    gr::Text      mNameText;
    gr::Text      mJobText;
    gr::Text      mLevelText;
    gr::Text      mHPText;
    gr::RatioBar  mHPBar;
    gr::Text      mSpdCntText;
    gr::Text      mAtkText;
    gr::Text      mDefText;
    gr::Text      mMobText;
    gr::Text      mEvadeText;
    gr::Text      mSpeedText;

};

}

#endif // CHARACINFO_HPP_INCLUDED
