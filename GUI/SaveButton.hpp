#ifndef StdActionVEBUTTON_HPP_INCLUDED
#define StdActionVEBUTTON_HPP_INCLUDED

#include "GUI/Component.hpp"
#include "Sound/SoundPlayer.hpp"
#include "States/Arch/Context.hpp"
#include "Graphism/Text.hpp"
#include "XML/pugixml.hpp"

#include <SFML/Graphics/Rect.hpp>

namespace GUI
{

class SaveButton : public Component
{
public:
    typedef std::shared_ptr<SaveButton> SPtr;
    typedef std::function<void()> Callback;

                    SaveButton(int number, pugi::xml_node file, st::Context context);
                    ~SaveButton();

    void            setCallback(Callback callback);
    virtual bool    isSelectable() const;
    virtual void	select();
    virtual void	deselect();

    virtual void	activate();
    virtual void	deactivate();

    virtual bool    contains(sf::Vector2f point) const;
    virtual bool    contains(float x, float y) const;

    virtual bool	handleEvent(const Input::Event& event);
    virtual void    update(sf::Time delta);

private:
    virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;

    Callback		            mCallback;
    std::vector<gr::Text>	mTexts;
    sf::RectangleShape          mFrame;
    Sound::SoundPlayer&         mSounds;
};

}

#endif // StdActionVEBUTTON_HPP_INCLUDED
