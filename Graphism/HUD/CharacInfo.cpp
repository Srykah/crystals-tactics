#include "Graphism/HUD/CharacInfo.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "Gameplay/General/Routines.hpp"
#include <sstream>

namespace gr
{

CharacInfo::CharacInfo(st::Context context, Character* charac)
: mBackground(sf::Vector2f(350, 150))
, mCharacter(charac)
, mFace(sf::Vector2f(100,100))
, mNameText("", context.fonts->get(Fonts::Main), 10, gr::Text::Shadow, sf::Color(255,192,0))
, mJobText("", context.fonts->get(Fonts::Main), 10, gr::Text::Shadow, sf::Color(255,192,0))
, mLevelText("", context.fonts->get(Fonts::Main), 10, gr::Text::Shadow, sf::Color(255,192,0))
, mHPText("", context.fonts->get(Fonts::Main), 10, gr::Text::Shadow, sf::Color(255,192,0))
, mHPBar(1, sf::Vector2f(270, 20), sf::Color::Green, false)
, mSpdCntText("", context.fonts->get(Fonts::Main), 10, gr::Text::Shadow, sf::Color(255,192,0))
, mAtkText("", context.fonts->get(Fonts::Main), 10, gr::Text::Shadow, sf::Color(255,192,0))
, mDefText("", context.fonts->get(Fonts::Main), 10, gr::Text::Shadow, sf::Color(255,192,0))
, mMobText("", context.fonts->get(Fonts::Main), 10, gr::Text::Shadow, sf::Color(255,192,0))
, mEvadeText("", context.fonts->get(Fonts::Main), 10, gr::Text::Shadow, sf::Color(255,192,0))
, mSpeedText("", context.fonts->get(Fonts::Main), 10, gr::Text::Shadow, sf::Color(255,192,0))
{
    placeThings();
    fillTexts();

    mBackground.setFillColor(sf::Color(32,32,64));
    mFace.setFillColor(sf::Color(128,128,128));
}

CharacInfo::~CharacInfo()
{

}

void CharacInfo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mBackground, states);

    target.draw(mFace, states);
    target.draw(mNameText, states);
    target.draw(mJobText, states);
    target.draw(mLevelText, states);
    target.draw(mHPText, states);
    target.draw(mHPBar, states);
    target.draw(mSpdCntText, states);
    target.draw(mAtkText, states);
    target.draw(mDefText, states);
    target.draw(mMobText, states);
    target.draw(mEvadeText, states);
    target.draw(mSpeedText, states);
}

void CharacInfo::update(sf::Time dt)
{
    if (mCharacter != nullptr)
    {
        if (mCharacter->getHP() != mHPCache)
        {
            mHPCache = mCharacter->getHP();
            std::wstringstream ss;
            ss << "PV : " << mCharacter->getHP() << " / " << mStatsCache.maxHP;
            mHPText.setString(ss.str());
            mHPBar.setRatio(mCharacter->getHP(), mCharacter->getStats().maxHP);
        }
        if (mCharacter->getStats().attack != mStatsCache.attack)
        {
            mStatsCache.attack = mCharacter->getStats().attack;
            std::wstringstream ss;
            ss << "Att : " << mCharacter->getStats().attack;
            mAtkText.setString(ss.str());
        }
        if (mCharacter->getStats().defense != mStatsCache.defense)
        {
            mStatsCache.defense = mCharacter->getStats().defense;
            std::wstringstream ss;
            ss << sf::String("Def : ").toWideString() << mCharacter->getStats().defense;
            mDefText.setString(ss.str());
        }
        if (mCharacter->getStats().mobility != mStatsCache.mobility)
        {
            mStatsCache.mobility = mCharacter->getStats().mobility;
            std::wstringstream ss;
            ss << "Mob : " << mCharacter->getStats().mobility;
            mMobText.setString(ss.str());
        }
        if (mCharacter->getStats().evasion != mStatsCache.evasion)
        {
            mStatsCache.evasion = mCharacter->getStats().evasion;
            std::wstringstream ss;
            ss << "Esq : " << mCharacter->getStats().evasion;
            mEvadeText.setString(ss.str());
        }
        if (mCharacter->getStats().speed != mStatsCache.speed)
        {
            mStatsCache.speed = mCharacter->getStats().speed;
            std::wstringstream ss;
            ss << "Vit : " << mCharacter->getStats().speed;
            mSpeedText.setString(ss.str());
        }
        if (mCharacter->getLevel() != mLvlCache)
        {
            mLvlCache = mCharacter->getLevel();
            std::wstringstream ss;
            ss << "Niv : " << mCharacter->getLevel();
            mLevelText.setString(ss.str());
        }
        if (mCharacter->getSpeedCounter() != mSpdCntCache)
        {
            mSpdCntCache = mCharacter->getSpeedCounter();
            std::wstringstream ss;
            ss << "CT : " << mCharacter->getSpeedCounter();
            mSpdCntText.setString(ss.str());
        }
    }
}

void CharacInfo::handleEvent(const Input::Event& event)
{

}

void CharacInfo::setCharacter(Character* charac)
{
    mCharacter = charac;
    fillTexts();
}

void CharacInfo::placeThings()
{
    mFace.setPosition(10,40);

    mNameText.setPosition(120,40);
    mJobText.setPosition(120, 65);
    mLevelText.setPosition(225, 65);

    mHPBar.setPosition(70, 10);
    mHPText.setPosition(280, 40);

    mSpdCntText.setPosition(280, 65);

    mAtkText.setPosition(120, 90);
    mDefText.setPosition(120, 120);

    mMobText.setPosition(195, 120);
    mEvadeText.setPosition(195, 90);
    mSpeedText.setPosition(270, 90);
}

void CharacInfo::fillTexts()
{
    if (mCharacter != nullptr)
    {
        mStatsCache = mCharacter->getStats();
        mHPCache = mCharacter->getHP();
        mLvlCache = mCharacter->getLevel();
        mSpdCntCache = mCharacter->getSpeedCounter();

        std::wstringstream ss;

        mNameText.setString(mCharacter->getName());
        mJobText.setString(CharTypeToStr(mCharacter->getType()));

        ss << "Nv : " << mCharacter->getLevel();
        mLevelText.setString(ss.str());

        ss.str(sf::String().toWideString());
        ss << "PV : " << mCharacter->getHP() << " / " << mStatsCache.maxHP;
        mHPText.setString(ss.str());
        mHPBar.setRatio(mCharacter->getHP(), mStatsCache.maxHP);

        ss.str(sf::String().toWideString());
        ss << "Att : " << mStatsCache.attack;
        mAtkText.setString(ss.str());

        ss.str(sf::String().toWideString());
        ss << sf::String("Déf : ").toWideString() << mStatsCache.defense;
        mDefText.setString(ss.str());

        ss.str(sf::String().toWideString());
        ss << "Mob : " << mStatsCache.mobility;
        mMobText.setString(ss.str());

        ss.str(sf::String().toWideString());
        ss << "Esq : " << mStatsCache.evasion;
        mEvadeText.setString(ss.str());

        ss.str(sf::String().toWideString());
        ss << "Vit : " << mStatsCache.speed;
        mSpeedText.setString(ss.str());

        ss.str(sf::String().toWideString());
        ss << "CT : " << mCharacter->getSpeedCounter() << " / 100";
        mSpdCntText.setString(ss.str());
    }
    else
    {
        mNameText.setString("");
        mJobText.setString("");
        mLevelText.setString("Nv : ");
        mHPText.setString("PV :  / ");
        mAtkText.setString("Att : ");
        mDefText.setString("Déf : ");
        mMobText.setString("Mob : ");
        mEvadeText.setString("Esq : ");
        mSpeedText.setString("Vit : ");
        mSpdCntText.setString("CT :  / 100");
    }
}

}
