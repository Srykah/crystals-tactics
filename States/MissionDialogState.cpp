#include "../States/MissionDialogState.hpp"
#include "../Other/Utility.hpp"
#include <cstring>
#include <sstream>

#include <iostream>

MissionDialogState::ScreenPosition MissionDialogState::convertStringToScreenPosition(const std::string& str)
{
    if (str == "Left1") return Left1;
    else if (str == "Left2") return Left2;
    else if (str == "Left3") return Left3;
    else if (str == "Right1") return Right1;
    else if (str == "Right2") return Right2;
    else if (str == "Right3") return Right3;
    else return Out;
}


MissionDialogState::DialogCharacter::DialogCharacter(const std::string& characterFile)
: screenPos(Out)
{
    doc.load_file(characterFile.c_str());
    node = doc.child("character");
}


MissionDialogState::MissionDialogState(StateStack& stack, State::Context& context, const StateData& data)
: State(stack, context)
, mNothingDoneYet(true)
, mNode(data.node())
, mIt(data.node().child("scene").begin())
, mTextBackground(sf::Vector2f(1000.f, 200.f))
, mText("", context.fonts->get(Fonts::Main))
{
    mTextBackground.setFillColor(sf::Color::Blue);
    mTextBackground.setOutlineColor(sf::Color::White);
    mTextBackground.setOutlineThickness(-5);
    mTextBackground.setOrigin(500.f, 100.f);
    mTextBackground.setPosition(683.f, 500.f);
    mText.setPosition(683.f, 500.f);

    mLeftSprite1.setPosition(183, 384);
    mLeftSprite2.setPosition(383, 384);
    mLeftSprite3.setPosition(583, 384);
    mRightSprite1.setPosition(783, 384);
    mRightSprite2.setPosition(983, 384);
    mRightSprite3.setPosition(1183, 384);

    mRightSprite1.setScale(-1,1);
    mRightSprite2.setScale(-1,1);
    mRightSprite3.setScale(-1,1);

    loadTextures();
}

MissionDialogState::~MissionDialogState()
{

}

void MissionDialogState::draw()
{
    sf::RenderWindow& window(*getContext().window);

    window.draw(sf::Sprite(mBackground));

    window.draw(mLeftSprite3);
    window.draw(mLeftSprite2);
    window.draw(mLeftSprite1);
    window.draw(mRightSprite3);
    window.draw(mRightSprite2);
    window.draw(mRightSprite1);

    window.draw(mTextBackground);
    window.draw(mText);
}

bool MissionDialogState::update(sf::Time dt)
{
    if (mNothingDoneYet)
        readForward();

    return true;
}

bool MissionDialogState::handleInput(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos)
{
    if (stdAction == IH::Start)
    {
        setData(StateData(true));
        requestStackClose();
    }
    if (stdAction == IH::A)
    {
        readForward();
    }

    return false;
}

States::ID MissionDialogState::getID() const
{
    return States::MissionDialog;
}

void MissionDialogState::loadTextures()
{
    mBackground.loadFromFile(mNode.child("background").attribute("path").as_string());

    for(pugi::xml_node& character : mNode.child("characters"))
        mCharacters.emplace(std::piecewise_construct,
          std::forward_as_tuple(std::string(character.attribute("name").as_string())),
          std::forward_as_tuple(std::string(character.attribute("file").as_string())));
}

void MissionDialogState::readForward()
{
    if (!mNothingDoneYet && mIt != mNode.child("scene").end() && mIt->name() != std::string("end"))
        mIt++;
    else
        mNothingDoneYet = false;

    if (mIt == mNode.child("scene").end() || mIt->name() == std::string("end"))
    {
        setData(StateData(true));
        requestStackClose();
    }
    else if (mIt->name() == std::string("attitude"))
    {
        // dc is a reference to the character of given name stored in the array
        DialogCharacter& dc = mCharacters.at(mIt->attribute("character").as_string());

        // its texture is set to the image pointed at the path of its new attitude
        dc.texture.loadFromFile(dc.node.child(mIt->attribute("new_attitude").as_string()).attribute("path").as_string());

        // we reset the texture rect of the corresponding sprite
        if (dc.screenPos == Left1)
            mLeftSprite1.setTexture(*mLeftSprite1.getTexture(), true);
        else if (dc.screenPos == Left2)
            mLeftSprite2.setTexture(*mLeftSprite2.getTexture(), true);
        else if (dc.screenPos == Left3)
            mLeftSprite3.setTexture(*mLeftSprite3.getTexture(), true);
        else if (dc.screenPos == Right1)
            mRightSprite1.setTexture(*mRightSprite1.getTexture(), true);
        else if (dc.screenPos == Right2)
            mRightSprite2.setTexture(*mRightSprite2.getTexture(), true);
        else if (dc.screenPos == Right3)
            mRightSprite3.setTexture(*mRightSprite3.getTexture(), true);

        // finally, we check the next step (we always want to finish on new text)
        readForward();
    }
    else if (mIt->name() == std::string("position"))
    {
        // dc is a reference to the character of given name stored in the array
        DialogCharacter& dc = mCharacters.at(mIt->attribute("character").as_string());

        // we check where he was so that we reset the sprite there
        switch (dc.screenPos)
        {
        case Left1:
            mLeftSprite1.setTexture(sf::Texture());
            break;

        case Left2:
            mLeftSprite2.setTexture(sf::Texture());
            break;

        case Left3:
            mLeftSprite3.setTexture(sf::Texture());
            break;

        case Right1:
            mRightSprite1.setTexture(sf::Texture());
            break;

        case Right2:
            mRightSprite2.setTexture(sf::Texture());
            break;

        case Right3:
            mRightSprite3.setTexture(sf::Texture());
            break;
        }

        // then we change the intern position
        dc.screenPos = convertStringToScreenPosition(mIt->attribute("new_position").as_string());

        // and finally we show him on screen at its new position
        switch (dc.screenPos)
        {
        case Left1:
            mLeftSprite1.setTexture(dc.texture);
            centerOrigin(mLeftSprite1);
            break;

        case Left2:
            mLeftSprite2.setTexture(dc.texture);
            centerOrigin(mLeftSprite2);
            break;

        case Left3:
            mLeftSprite3.setTexture(dc.texture);
            centerOrigin(mLeftSprite3);
            break;

        case Right1:
            mRightSprite1.setTexture(dc.texture);
            centerOrigin(mRightSprite1);
            break;

        case Right2:
            mRightSprite2.setTexture(dc.texture);
            centerOrigin(mRightSprite2);
            break;

        case Right3:
            mRightSprite3.setTexture(dc.texture);
            centerOrigin(mRightSprite3);
            break;
        }

        // finally, we check the next step (we always want to finish on new text)
        readForward();
    }
    else if (mIt->name() == std::string("text"))
    {
        mText.setString(mIt->child_value());
        centerOrigin(mText);
    }
}
