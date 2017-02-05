#ifndef MISSIONDIALOGSTATE_HPP_INCLUDED
#define MISSIONDIALOGSTATE_HPP_INCLUDED

#include "../StatesArch/State.hpp"
#include <string>
#include <map>
#include <SFML/Graphics/Text.hpp>
#include "../Graphism/Text.hpp"

/*
Need to implement readForward
*/

class MissionDialogState : public State
{
public:
    MissionDialogState(StateStack& stack, State::Context& context, const StateData& data);
    ~MissionDialogState();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleInput(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos);
    virtual States::ID  getID() const;

private:
    enum ScreenPosition
    {
        Out,
        Left1,
        Left2,
        Left3,
        Right1,
        Right2,
        Right3
    };

    static ScreenPosition convertStringToScreenPosition(const std::string& str);

    struct DialogCharacter
    {
        DialogCharacter(const std::string& characterFile);

        pugi::xml_node node;
        sf::Texture texture;
        ScreenPosition screenPos;

    private:
        pugi::xml_document doc;
    };

private:
    void loadTextures();
    void readForward();

private:
    bool mNothingDoneYet;

    pugi::xml_node mNode;
    pugi::xml_node_iterator mIt;

    sf::Texture mBackground;

    std::map< std::string, DialogCharacter > mCharacters;
    sf::Sprite mLeftSprite1, mLeftSprite2, mLeftSprite3, mRightSprite1, mRightSprite2, mRightSprite3;

    sf::RectangleShape mTextBackground;
    Graphism::Text mText;
};

#endif // MISSIONDIALOGSTATE_HPP_INCLUDED
