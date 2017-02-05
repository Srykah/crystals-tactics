#ifndef NEWGAMESTATE_HPP_INCLUDED
#define NEWGAMESTATE_HPP_INCLUDED

#include "../StatesArch/State.hpp"
#include <vector>
#include <string>
#include "../Graphism/Text.hpp"

class NewGameState : public State
{
public:
    NewGameState(StateStack& stack, State::Context& context, const StateData& data);
    ~NewGameState();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleInput(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos);
    virtual States::ID  getID() const;

private:
    void loadImages();
    void prepareSlides();
    void init();
    void createCharacters(Guild& guild);

private:
    int mSpeechStep;
    TextureHolder mTextures;
    sf::Sprite mSprite;
    std::vector<sf::String> mStrings;
    std::vector<Textures::ID> mTexIDTab;
    std::vector<bool> mPositions;
    std::vector<sf::Time> mTimes;
    Graphism::Text mText;
    sf::Time mTimeCounter;
    sf::RectangleShape mTextZone;
    const sf::Vector2f UP_POS, MID_POS;
};

#endif // NEWGAMESTATE_HPP_INCLUDED
