#include "States/Menu/MissionDialogue.hpp"
#include "States/Arch/StateStack.hpp"
#include "States/Gameplay/BattleMain.hpp"
#include "Other/Utility.hpp"
#include <stdexcept>
#include <cstring>
#include <sstream>

namespace st
{

MissionDialogue::ScreenPosition MissionDialogue::StrToScreenPosition(const sf::String& str)
{
         if (str == "Left1")  return Left1;
    else if (str == "Left2")  return Left2;
    else if (str == "Left3")  return Left3;
    else if (str == "Right1") return Right1;
    else if (str == "Right2") return Right2;
    else if (str == "Right3") return Right3;
    else                      return Out;
}


MissionDialogue::DialogCharacter::DialogCharacter(const char* characterFile)
: screenPos(Out)
, docPtr(new pugi::xml_document)
{
    docPtr->load_file(characterFile);
    if (!*docPtr)
    {
        std::stringstream ss;
        ss << "DialogCharacter error : couldn't open / read dialog character file " << characterFile;
        throw std::runtime_error(ss.str());
    }

    node = docPtr->child("character");
    name = docPtr->child("character").attribute("name").as_string("???");
}


MissionDialogue::MissionDialogue(StateStack* stack, Context context, const pugi::xml_node& node)
: State(stack, context)
, mBaseNode(node)
, mSceneNode(node.child("scene").first_child())
, mTextBackground(sf::Vector2f(1000.f, 200.f))
, mText("", context.fonts->get(Fonts::Main))
{
    mTextBackground.setFillColor(sf::Color::Blue);
    mTextBackground.setOutlineColor(sf::Color::White);
    mTextBackground.setOutlineThickness(-5);
    mTextBackground.setOrigin(500.f, 100.f);
    mTextBackground.setPosition(683.f, 600.f);
    mText.setFillColor(sf::Color::White);
    mText.setPosition(683.f, 600.f);

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
    read();
}

MissionDialogue::~MissionDialogue()
{

}

void MissionDialogue::draw()
{
    sf::RenderWindow& window(*mContext.window);

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

bool MissionDialogue::update(sf::Time dt)
{
    return true;
}

bool MissionDialogue::handleEvent(const Input::Event& event)
{
    if (event.stdAc == Input::Start)
    {
        endDialogue();
    }
    else if (event.stdAc == Input::A)
    {
        if (mSceneNode)
            read();
        else
            endDialogue();
    }

    return false;
}

bool MissionDialogue::handleSignal(const Signal& signal)
{
    return true;
}

void MissionDialogue::loadTextures()
{
    mBackground.loadFromFile(mBaseNode.child("background").attribute("path").as_string());

    for(pugi::xml_node& character : mBaseNode.child("characters"))
        mCharacters.emplace_back(character.attribute("file").as_string());
}

void MissionDialogue::read()
{
    bool readAgain(false);

    sf::String nodeName(mSceneNode.name());

    if (nodeName == "attitude")
    {
        // dc is a reference to the character of given name stored in the array
        DialogCharacter& dc = mCharacters.at(mSceneNode.attribute("char").as_int(-1));

        // its texture is set to the image pointed at the path of its new attitude
        dc.texture.loadFromFile(dc.node.child(mSceneNode.attribute("new_att").as_string()).attribute("path").as_string());

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
        readAgain = true;
    }
    else if (nodeName == "position")
    {
        // dc is a reference to the character of given name stored in the array
        DialogCharacter& dc = mCharacters.at(mSceneNode.attribute("char").as_int(-1));

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
        dc.screenPos = StrToScreenPosition(mSceneNode.attribute("new_pos").as_string());

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
        readAgain = true;
    }
    else if (nodeName == "caption")
    {
        mText.setString(mSceneNode.text().as_string());
        mText.setStyle(sf::Text::Italic);
        centerOrigin(mText);
    }
    else if (nodeName == "line")
    {
        if (mSceneNode.attribute("masked"))
        {
            sf::String str("??? : ");
            str += mSceneNode.text().as_string();
            mText.setString(str);
            mText.setStyle(sf::Text::Regular);
            centerOrigin(mText);
        }
        else
        {
            sf::String str(mCharacters.at(mSceneNode.attribute("char").as_int(-1)).name);
            str += " : ";
            str += mSceneNode.text().as_string();
            mText.setString(str);
            mText.setStyle(sf::Text::Regular);
            centerOrigin(mText);
        }
    }

    mSceneNode = mSceneNode.next_sibling();
    if (readAgain && mSceneNode)
        read();
}

void MissionDialogue::endDialogue()
{
    mStack->close(this);
    pugi::xml_node next(mBaseNode.next_sibling());
    if (!next)
        mStack->clear();
    else if (!std::strcmp(next.name(), "battle"))
        mStack->push(new Battle(mStack, mContext, next), true);
}

}
