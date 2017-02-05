#include "../GUI/TextField.hpp"
#include "../Other/Utility.hpp"
#include <string>

bool isAValidString(const sf::String& str)
{
    return str.toWideString().find_first_not_of(sf::String(" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\
                                                           -_.:/!;\\\'\"|()[]{}\
                                                           ��������������������������").toWideString()) == std::wstring::npos;
}

GUI::TextField::TextField(State::Context context,
                          sf::String* returnString,
                          sf::String fieldName,
                          sf::String defaultString)
: mInputString(defaultString)
, mReturnString(returnString)
, mFieldName(fieldName, context.fonts->get(Fonts::Main))
, mTextEntered(mInputString, context.fonts->get(Fonts::Main))
, mTextBox(context.textures->get(Textures::TextField))
, mCursor(sf::Lines)
, mSelectionWidth(0)
{
    mCursor.append(sf::Vertex(sf::Vector2f(), sf::Color::White));
    mCursor.append(sf::Vertex(sf::Vector2f(), sf::Color::White));
    mFieldName.setPosition(50, 50);
    mTextEntered.setPosition(50, 100);
    setCursorPos(0);
}

GUI::TextField::~TextField()
{

}

void GUI::TextField::setDefaultString(sf::String defaultString)
{
    mTextEntered.setString(defaultString);
}

bool GUI::TextField::isSelectable() const
{
    return true;
}

bool GUI::TextField::contains(sf::Vector2f point) const
{
    return getTransform().transformRect(mTextBox.getGlobalBounds()).contains(point);
}

bool GUI::TextField::contains(float x, float y) const
{
    return contains(sf::Vector2f(x,y));
}

bool GUI::TextField::handleInput(const sf::Event& event, IH::SA stdAc, sf::Vector2f mousePos)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Left and mCursorPos > 0)
        {
            setCursorPos(mCursorPos-1);
            return false;
        }
        else if (event.key.code == sf::Keyboard::Right and mCursorPos < mInputString.getSize())
        {
            setCursorPos(mCursorPos+1);
            return false;
        }
        else if (event.key.code == sf::Keyboard::End)
        {
            setCursorPos(mInputString.getSize());
            return false;
        }
        else if (event.key.code == sf::Keyboard::Home)
        {
            setCursorPos(0);
            return false;
        }
        else if (event.key.code == sf::Keyboard::BackSpace and mCursorPos > 0)
        {
            mInputString.erase(mCursorPos-1);
            mTextEntered.setString(mInputString);
            setCursorPos(mCursorPos-1);
            return false;
        }
        else if (event.key.code == sf::Keyboard::Delete and mCursorPos < mInputString.getSize())
        {
            mInputString.erase(mCursorPos);
            mTextEntered.setString(mInputString);
            return false;
        }
        else if (event.key.code == sf::Keyboard::Return)
        {
            *mReturnString = mInputString;
            deactivate();
            return false;
        }
    }
    if (event.type == sf::Event::TextEntered and isAValidString(event.text.unicode))
    {
        mInputString.insert(mCursorPos, event.text.unicode);
        mTextEntered.setString(mInputString);
        setCursorPos(mCursorPos+1);
        return false;
    }

    return true;
}
void GUI::TextField::update(sf::Time delta)
{
    if (isSelected())
    {
        mCursorBlinkTime += delta;
        mCursorBlinkTime %= sf::seconds(1.f);
    }
}

void GUI::TextField::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mTextBox, states);
    target.draw(mFieldName, states);
    target.draw(mTextEntered, states);
    if (mCursorBlinkTime < sf::seconds(0.5))
        target.draw(mCursor, states);
}

void GUI::TextField::setCursorPos(int pos)
{
    mCursor[0].position = sf::Vector2f(mTextEntered.findCharacterPos(pos));
    mCursor[1].position = sf::Vector2f(mTextEntered.findCharacterPos(pos).x, mTextEntered.findCharacterPos(1).y+1.5*mTextEntered.getCharacterSize());
    mCursorPos = pos;
}
