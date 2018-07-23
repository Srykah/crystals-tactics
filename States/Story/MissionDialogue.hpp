#ifndef MISSIONDIALOGSTATE_HPP_INCLUDED
#define MISSIONDIALOGSTATE_HPP_INCLUDED

#include "States/Arch/State.hpp"
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>

namespace st
{

class MissionDialogue : public State
{
public:
    MissionDialogue(StateStack* stack, Context context, const pugi::xml_node& node);
    ~MissionDialogue();

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const Input::Event& event);
    virtual bool        handleSignal(const Signal& signal);

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

    static ScreenPosition StrToScreenPosition(const sf::String& str);

    struct DialogCharacter
    {
        DialogCharacter(const char* characterFile);

        pugi::xml_node node;
        sf::String name;
        sf::Texture texture;
        ScreenPosition screenPos;

    private:
        std::unique_ptr<pugi::xml_document> docPtr;
    };

private:
    void loadTextures();
    void read();

private:
    pugi::xml_node mBaseNode;
    pugi::xml_node mSceneNode;

    sf::Texture mBackground;

    std::vector<DialogCharacter> mCharacters;
    sf::Sprite mLeftSprite1, mLeftSprite2, mLeftSprite3, mRightSprite1, mRightSprite2, mRightSprite3;

    sf::RectangleShape mTextBackground;
    sf::Text mText;
};

}

#endif // MISSIONDIALOGSTATE_HPP_INCLUDED
