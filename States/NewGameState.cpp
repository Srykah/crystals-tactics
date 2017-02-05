#include "../States/NewGameState.hpp"
#include "../Gameplay/Guild.hpp"
#include "../Other/Utility.hpp"

NewGameState::NewGameState(StateStack& stack, State::Context& context, const StateData& data)
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
    createCharacters(*getContext().guild);
}

NewGameState::~NewGameState()
{

}

void NewGameState::draw()
{
    sf::RenderWindow& window(*getContext().window);
    window.draw(mSprite);
    window.draw(mTextZone);
    window.draw(mText);
}

bool NewGameState::update(sf::Time dt)
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
        requestStackClear();
        requestStackPush(States::Mission, std::string("Media/Missions/Tutorial.xml"));
    }

    return false;
}

bool NewGameState::handleInput(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos)
{
    if (stdAction == IH::Start)
    {
        requestStackClear();
        requestStackPush(States::Mission, std::string("Media/Missions/Tutorial.xml"));
    }

    return false;
}

States::ID NewGameState::getID() const
{
    return States::NewGame;
}

void NewGameState::loadImages()
{
    mTextures.load(Textures::Moon,          "Media/Textures/Story/Moon.jpg");
    mTextures.load(Textures::Meteorites,    "Media/Textures/Story/Meteorites.jpg");
    mTextures.load(Textures::Ocean,         "Media/Textures/Story/Ocean.jpg");
    mTextures.load(Textures::Desert,        "Media/Textures/Story/Desert.jpg");
    mTextures.load(Textures::Volcano,       "Media/Textures/Story/Volcano.jpg");
    mTextures.load(Textures::Crystals,      "Media/Textures/Story/Crystals.png");
}

void NewGameState::prepareSlides()
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

void NewGameState::init()
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

void NewGameState::createCharacters(Guild& guild)
{
    guild.addMember(new Character("Srykah",       Character::Tank,        5, getContext()));
    guild.addMember(new Character("Landswalker",  Character::Tank,        3, getContext()));
    guild.addMember(new Character("Nashunn",      Character::Medic,       3, getContext()));
    guild.addMember(new Character("Azox",         Character::Medic,       3, getContext()));
    guild.addMember(new Character("Ersi",         Character::Murderer,    3, getContext()));
    guild.addMember(new Character("Sidysky",      Character::Mechanics,   3, getContext()));
    guild.addMember(new Character("Sweps",        Character::Gunner,      3, getContext()));

    guild.getMember(0)->setTarget(); //perso ppal => game over s'il meurt

    // mettre l'équipement ici
}
