#include "Graphism/HUD/RatioBar.hpp"

gr::RatioBar::RatioBar(float ratio, sf::Vector2f size, sf::Color color, bool increase)
: mOutsideBar(size)
{
    setColor(color);
    setIncrease(increase);
    setRatio(ratio);
}

gr::RatioBar::~RatioBar()
{

}

void gr::RatioBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mOutsideBar, states);
    target.draw(mInsideBar, states);
}

void gr::RatioBar::setColor(sf::Color color)
{
    mOutsideBar.setFillColor(color*sf::Color(128,128,128));
    mInsideBar.setFillColor(color);
}

void gr::RatioBar::setIncrease(bool flag)
{
    mIncrease = flag;

    sf::Vector2f size = mOutsideBar.getSize();
    float thickness = size.y * 0.1;

    if (flag)
    {
        mInsideBar.setPosition(thickness, thickness);
        mInsideBar.setRotation(0.f);
    }
    else
    {
        mInsideBar.setPosition(size.x-thickness, size.y-thickness);
        mInsideBar.setRotation(180.f);
    }
}

void gr::RatioBar::setRatio(float ratio)
{
    if (ratio <= 1.f)
    {
        mRatio = ratio;
        sf::Vector2f size = mOutsideBar.getSize();
        float thickness = size.y * 0.1;
        mInsideBar.setSize(sf::Vector2f((size.x-2.f*thickness)*ratio, size.y-2.f*thickness));
    }
    else
        setRatio(1.f);
}

void gr::RatioBar::setRatio(float num, float den)
{
    if (den <= 1e-4)
        setRatio(1.f);
    setRatio(num/den);
}

float gr::RatioBar::getRatio() const
{
    return mRatio;
}
