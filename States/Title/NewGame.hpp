#ifndef NEWGAMESTATE_HPP_INCLUDED
#define NEWGAMESTATE_HPP_INCLUDED

#include "States/Arch/State.hpp"
#include <vector>
#include <SFML/System/String.hpp>
#include "Graphism/General/Text.hpp"

namespace st
{

class NewGame : public State
{
public:
    NewGame(StateStack* stack, Context context);
    ~NewGame();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);

private:
    void loadImages();
    void prepareSlides();
    void init();
    void createCharacters();

private:
    int mSpeechStep;
    dt::TextureHolder mTextures;
    sf::Sprite mSprite;
    std::vector<sf::String> mStrings;
    std::vector<Textures::ID> mTexIDTab;
    std::vector<bool> mPositions;
    std::vector<sf::Time> mTimes;
    gr::Text mText;
    sf::Time mTimeCounter;
    sf::RectangleShape mTextZone;
    const sf::Vector2f UP_POS, MID_POS;
};

}

#endif // NEWGAMESTATE_HPP_INCLUDED
