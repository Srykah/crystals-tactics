#include "States/Menu/NewGame.hpp"
#include "States/Arch/StateStack.hpp"
#include "States/Gameplay/Mission.hpp"
#include "Gameplay/Story/Guild.hpp"
#include "Other/Utility.hpp"

namespace States
{

NewGame::NewGame(StateStack* stack, Context context)
: State(stack, context)
, mSpeechStep(0)
, mText("", context.fonts->get(Fonts::Main))
, mTextZone(sf::Vector2f(1000.f, 200.f))
, UP_POS(sf::Vector2f(683.f, 300.f))
, MID_POS(sf::Vector2f(683.f, 384.f))
{
    loadImages();
    prepareSlides();
    init();
    createCharacters();
}

NewGame::~NewGame()
{

}

void NewGame::draw()
{
    sf::RenderWindow& window(*mContext.window);
    window.draw(mSprite);
    window.draw(mTextZone);
    window.draw(mText);
}

bool NewGame::update(sf::Time dt)
{
    mTimeCounter += dt;
    if (mSpeechStep < mStrings.size()-1 && mTimeCounter > mTimes[mSpeechStep]) // si on doit changer de diapo
    {
        mTimeCounter = sf::Time::Zero;
        mSpeechStep++;

        mSprite.setTexture(mTextures.get(mTexIDTab[mSpeechStep]), true);
        mSprite.setPosition(mPositions[mSpeechStep] ? UP_POS : MID_POS);
        mText.setString(mStrings[mSpeechStep]);
        centerOrigin(mSprite);
        centerOrigin(mText);
    }
    else if (mTimeCounter > mTimes.back()) // si on a fini la présentation
    {
        mStack->clear();
        mStack->push(new Mission(mStack, mContext, "Media/Missions/Tutorial.xml"));
    }

    return false;
}

bool NewGame::handleEvent(const Input::Event& event)
{
    if (event.stdAc == Input::Start)
    {
        mStack->clear();
        mStack->push(new Mission(mStack, mContext, "Media/Missions/Tutorial.xml"));
    }

    return false;
}

bool NewGame::handleSignal(const Signal& signal)
{
    return true;
}

void NewGame::loadImages()
{
    mTextures.load(Textures::Moon,          "Media/Textures/Story/Moon.jpg");
    mTextures.load(Textures::Meteorites,    "Media/Textures/Story/Meteorites.jpg");
    mTextures.load(Textures::Ocean,         "Media/Textures/Story/Ocean.jpg");
    mTextures.load(Textures::Desert,        "Media/Textures/Story/Desert.jpg");
    mTextures.load(Textures::Volcano,       "Media/Textures/Story/Volcano.jpg");
    mTextures.load(Textures::Crystals,      "Media/Textures/Story/Crystals.png");
}

void NewGame::prepareSlides()
{
    mStrings.push_back("Plusieurs siècles avant notre ère, alors que l'humanité et sa technologie n'existait pas,\nla lune veillant sur notre planète était encore ronde.");
    mStrings.push_back("Une légende raconte qu'un jour, une comète la percuta lui arrachant un fragment,\nqui au contact de l'atmosphère se sépara en trois morceaux.");
    mStrings.push_back("Le premier morceau sombra dans les profondeurs de l'océan.");
    mStrings.push_back("Le deuxième fut perdu dans le désert et ses tempêtes.");
    mStrings.push_back("Le dernier tomba dans un volcan en éruption.");
    mStrings.push_back("Il est dit que les fragments devenus cristaux dégagent aujourd'hui une grande puissance...");

    mTexIDTab.push_back(Textures::Moon);
    mTexIDTab.push_back(Textures::Meteorites);
    mTexIDTab.push_back(Textures::Ocean);
    mTexIDTab.push_back(Textures::Desert);
    mTexIDTab.push_back(Textures::Volcano);
    mTexIDTab.push_back(Textures::Crystals);

    mPositions.push_back(true);
    mPositions.push_back(true);
    mPositions.push_back(false);
    mPositions.push_back(false);
    mPositions.push_back(false);
    mPositions.push_back(true);

    mTimes.push_back(sf::seconds(9.f));
    mTimes.push_back(sf::seconds(10.f));
    mTimes.push_back(sf::seconds(7.f));
    mTimes.push_back(sf::seconds(6.f));
    mTimes.push_back(sf::seconds(5.f));
    mTimes.push_back(sf::seconds(10.f));
}

void NewGame::init()
{
    mSprite.setTexture(mTextures.get(Textures::Moon));
    centerOrigin(mSprite);
    mSprite.setPosition(UP_POS);

    mTextZone.setFillColor(sf::Color(0,0,0,128));
    mTextZone.setOutlineColor(sf::Color(0,0,0,64));
    mTextZone.setOutlineThickness(-5);
    centerOrigin(mTextZone);
    mTextZone.setPosition(683.f, 650.f);

    mText.setString(mStrings[0]);
    centerOrigin(mText);
    mText.setPosition(683.f, 650.f);
}

void NewGame::createCharacters()
{
    mContext.guild->loadFromFile("Saves/Default.xml", mContext);
}

}
