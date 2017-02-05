#ifndef GUILDMENUBUTTON_HPP_INCLUDED
#define GUILDMENUBUTTON_HPP_INCLUDED

#include "../GUI/Component.hpp"
#include "../Sound/SoundPlayer.hpp"
#include "../StatesArch/State.hpp"
#include "../Graphism/Text.hpp"

#include <SFML/Graphics/Rect.hpp>

namespace GUI
{

class GuildMenuButton : public Component
{
public:
    typedef std::shared_ptr<GuildMenuButton>    SPtr;
    typedef std::function<void()>		        Callback;

    enum Type
    {
        MissionBoard,
        Shop,
        Clan,
        Exit
    };

                    GuildMenuButton(State::Context context, Type type);
                    ~GuildMenuButton();

    void            setCallback(Callback callback);
    virtual bool    isSelectable() const;
    virtual void	select();
    virtual void	deselect();

    virtual void	activate();
    virtual void	deactivate();

    virtual bool    contains(sf::Vector2f point) const;
    virtual bool    contains(float x, float y) const;

    virtual bool	handleInput(const sf::Event& event, InputHandler::StandardAction stdAction, sf::Vector2f mousePos);
    virtual void    update(sf::Time delta);

private:
    virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;

    Callback		mCallback;
    Graphism::Text	mText;
    sf::FloatRect   mBounds;
    SoundPlayer&	mSounds;
};

}

#endif // GUILDMENUBUTTON_HPP_INCLUDED
