#include "../States/SaveMenuState.hpp"
#include "../GUI/SaveButton.hpp"
#include "../Other/pugixml.hpp"
#include "../Other/Utility.hpp"
#include <stdexcept>

SaveMenuState::SaveMenuState(StateStack& stack, State::Context& context, const StateData& data)
: State(stack, context)
, mMessage("Choisissez le fichier de sauvegarde", context.fonts->get(Fonts::Main))
, mLoadingMode(data.boolean())
, mConfirmed(false)
, mBackground(sf::TrianglesFan, 6)
{
    centerOrigin(mMessage);
    mMessage.setPosition(683, 50);

    mBackground[0].position = sf::Vector2f(683, 384);
    mBackground[0].color = sf::Color(0,0,32);
    mBackground[1].position = sf::Vector2f(0, 0);
    mBackground[2].position = sf::Vector2f(1366, 0);
    mBackground[3].position = sf::Vector2f(1366, 768);
    mBackground[4].position = sf::Vector2f(0, 768);
    mBackground[5].position = sf::Vector2f(0, 0);
    for (int i(1); i < 6; i++)
        mBackground[i].color = sf::Color::Black;

    pugi::xml_document file1;
    if (!file1.load_file("Saves/save1.xml"))
        throw std::runtime_error("Unable to open save file 1");

    auto saveButton1 = std::make_shared<GUI::SaveButton>(1, file1.document_element(), context);
    saveButton1->setPosition(214, 433);
    mContainer.pack(saveButton1);

    pugi::xml_document file2;
    if (!file2.load_file("Saves/save2.xml"))
        throw std::runtime_error("Unable to open save file 2");

    auto saveButton2 = std::make_shared<GUI::SaveButton>(2, file2.document_element(), context);
    saveButton2->setPosition(334, 433);
    mContainer.pack(saveButton2);

    pugi::xml_document file3;
    if (!file3.load_file("Saves/save3.xml"))
        throw std::runtime_error("Unable to open save file 3");

    auto saveButton3 = std::make_shared<GUI::SaveButton>(3, file3.document_element(), context);
    saveButton3->setPosition(454, 433);
    mContainer.pack(saveButton3);
}

SaveMenuState::~SaveMenuState()
{

}

void SaveMenuState::draw()
{
    sf::RenderTarget& window = *getContext().window;

    window.draw(mBackground);
    window.draw(mMessage);
    window.draw(mContainer);
}

bool SaveMenuState::update(sf::Time dt)
{
    mContainer.update(dt);

    return true;
}

bool SaveMenuState::handleInput(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos)
{
    mContainer.handleInput(event, stdAction, mousePos);

    return false;
}

States::ID SaveMenuState::getID() const
{
    return States::SaveMenu;
}
