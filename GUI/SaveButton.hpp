#ifndef SAVEBUTTON_HPP_INCLUDED
#define SAVEBUTTON_HPP_INCLUDED

#include "../GUI/Component.hpp"
#include "../Sound/SoundPlayer.hpp"
#include "../StatesArch/State.hpp"
#include "../Graphism/Text.hpp"
#include "../Other/pugixml.hpp"

#include <SFML/Graphics/Rect.hpp>

namespace GUI
{

class SaveButton : public Component
{
public:
    typedef std::shared_ptr<SaveButton> SPtr;
    typedef std::function<void()> Callback;

                    SaveButton(int number, pugi::xml_node file, State::Context context);
                    ~SaveButton();

    void            setCallback(Callback callback);
    virtual bool    isSelectable() const;
    virtual void	select();
    virtual void	deselect();

    virtual void	activate();
    virtual void	deactivate();

    virtual bool    contains(sf::Vector2f point) const;
    virtual bool    contains(float x, float y) const;

    virtual bool	handleInput(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos);
    virtual void    update(sf::Time delta);

private:
    virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;

    Callback		mCallback;
    std::vector<Graphism::Text>	mTexts;
    sf::RectangleShape mFrame;
    SoundPlayer&	mSounds;
};

}

#endif // SAVEBUTTON_HPP_INCLUDED
