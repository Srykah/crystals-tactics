#ifndef RATIOBAR_HPP_INCLUDED
#define RATIOBAR_HPP_INCLUDED

#include <SFML/Graphics.hpp>

namespace Graphism
{

class RatioBar : public sf::Drawable, public sf::Transformable
{
public:
    RatioBar(float ratio = 1, sf::Vector2f size = sf::Vector2f(300.f,30.f), sf::Color color = sf::Color::Green, bool increase = true);
    ~RatioBar();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setIncrease(bool flag);
    void setColor(sf::Color color);
    void setRatio(float ratio);
    void setRatio(float num, float den);
    float getRatio() const;

private:
    float mRatio;
    bool mIncrease;
    sf::RectangleShape mOutsideBar, mInsideBar;
};


}

#endif // RATIOBAR_HPP_INCLUDED
