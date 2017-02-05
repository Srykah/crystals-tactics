#ifndef TEXTFIELD_HPP_INCLUDED
#define TEXTFIELD_HPP_INCLUDED

#include "../Graphism/Text.hpp"
#include <SFML/System/String.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Text.hpp>
#include "../GUI/Component.hpp"
#include "../StatesArch/State.hpp"
#include "../Input/InputHandler.hpp"

namespace GUI
{

class TextField : public Component
{
public:
    TextField(State::Context context,
              sf::String* returnString,
              sf::String fieldName,
              sf::String defaultString = sf::String());
    ~TextField();

    void setDefaultString(sf::String defaultString);

    virtual bool			    isSelectable() const;

    virtual bool                contains(sf::Vector2f point) const;
    virtual bool                contains(float x, float y) const;

    virtual bool	        	handleInput(const sf::Event& event, IH::SA stdAc, sf::Vector2f mousePos);
    virtual void                update(sf::Time delta);

private:
    virtual void                draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;

    void setCursorPos(int pos);

    sf::String mInputString;
    sf::String* mReturnString;
    Graphism::Text mFieldName;
    sf::Text mTextEntered;

    sf::Sprite mTextBox;

    sf::VertexArray mCursor;
    sf::Time mCursorBlinkTime;
    int mCursorPos;
    int mSelectionWidth;
};

}

#endif // TEXTFIELD_HPP_INCLUDED