#include "GUI/SaveButton.hpp"
#include "Graphism/Colors.hpp"
#include "Other/Utility.hpp"

namespace GUI
{

SaveButton::SaveButton(int number, pugi::xml_node file, States::Context context)
: mFrame(sf::Vector2f(500, 100))
, mSounds(*context.sounds)
{
    mFrame.setFillColor(Colors::RareGrey);
    mFrame.setOutlineColor(Colors::PlumBrown);
    mFrame.setOutlineThickness(-3);

    //number of the file
    mTexts.push_back(Graphism::Text("File no " + ToStr(number), context.fonts->get(Fonts::Main), 30, Graphism::Text::Shadow, Colors::Sand));
    mTexts[0].setPosition(5,5);

    //get hero node
    pugi::xml_node& hero = *std::find_if(file.child("characters").children().begin(), file.child("characters").children().end(), [](pugi::xml_node& node){ return node.attribute("storyStatus").as_string() == sf::String("Hero"); });

    //name of the hero
    mTexts.push_back(Graphism::Text(hero.attribute("name").as_string(), context.fonts->get(Fonts::Main), 30, Graphism::Text::Shadow, Colors::Sand));
    mTexts[1].setPosition(5, 40);

    //level of the hero
    mTexts.push_back(Graphism::Text(hero.attribute("level").as_string(), context.fonts->get(Fonts::Main), 30, Graphism::Text::Shadow, Colors::Sand));
    sf::FloatRect bounds = mTexts[2].getGlobalBounds();
    mTexts[2].setPosition(495-bounds.width, 40);

    //time of play
    mTexts.push_back(Graphism::Text(SecondsToStr(file.child("meta").attribute("playTime").as_int()),
                                    context.fonts->get(Fonts::Main), 30, Graphism::Text::Shadow, Colors::Sand));
    bounds = mTexts[3].getGlobalBounds();
    mTexts[3].setPosition(495-bounds.width, 5);
}

SaveButton::~SaveButton()
{

}

void SaveButton::setCallback(Callback callback)
{
	mCallback = std::move(callback);
}

bool SaveButton::isSelectable() const
{
    return true;
}

void SaveButton::select()
{
    if (!isSelected())
    {
        Component::select();
        mFrame.setOutlineColor(sf::Color::Yellow);
        mSounds.play(SoundEffect::ButtonSelect);
    }
}

void SaveButton::deselect()
{
    if (isSelected())
    {
        Component::deselect();
        mFrame.setOutlineColor(Colors::PlumBrown);
    }
}

void SaveButton::activate()
{
	Component::activate();

	if (mCallback)
        mCallback();

    mFrame.setOutlineColor(sf::Color::Red);
	mSounds.play(SoundEffect::ButtonActivate);

    deactivate();
}

void SaveButton::deactivate()
{
	Component::deactivate();
	if (isSelected())
        mFrame.setOutlineColor(sf::Color::Yellow);
    else
        mFrame.setOutlineColor(Colors::PlumBrown);
}

bool SaveButton::handleEvent(const Input::Event& event)
{
    return true;
}

void SaveButton::update(sf::Time delta)
{

}

void SaveButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mFrame);
	for (auto text : mTexts)
        target.draw(text, states);
}

bool SaveButton::contains(sf::Vector2f point) const
{
    return getTransform().transformRect(mFrame.getGlobalBounds()).contains(point);
}

bool SaveButton::contains(float x, float y) const
{
    return contains(sf::Vector2f(x,y));
}

}
