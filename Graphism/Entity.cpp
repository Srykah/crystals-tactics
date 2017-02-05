#include "../Graphism/Entity.hpp"
#include "../Other/pugixml.hpp"
#include <iostream>
#include <cassert>

namespace Graphism
{

Entity::Entity()
: mCurAnim(Animations::None)
, mFacing(Direction::Down)
{
    //mAnimations[std::make_pair(mCurAnim, mFacing)] = std::make_shared<Animation>();
}

Entity::~Entity()
{

}

bool Entity::loadFromNode(const pugi::xml_node& node)
{
    std::string textureFilename;
    textureFilename = node.attribute("spritesheet").as_string();

    std::cout << textureFilename << std::endl;

    sf::Texture texture;
    if(!texture.loadFromFile(textureFilename))
    {
        throw std::runtime_error("tex error");
        return false;
    }

    mSpriteSheet = std::make_shared<sf::Texture>(texture);

    for (auto anim : node.children("animation"))
    {
        Animations::Type type = stringToAT(anim.attribute("type").as_string());

        bool repeat = anim.attribute("repeat").as_bool();
        sf::Time duration = sf::milliseconds(anim.attribute("duration").as_int());

        for (auto facing : anim.children())
        {
            Direction::Dir dir = stringToDir(facing.name());

            auto animSPtr = std::make_shared<Animation>(mSpriteSheet.get());
            animSPtr->setRepeating(repeat);
            animSPtr->setDuration(duration);

            for (auto frame : facing.children())
            {
                sf::IntRect rect;
                sf::Vector2f origin;

                rect.left = frame.child("rect").attribute("left").as_int();
                rect.top = frame.child("rect").attribute("top").as_int();
                rect.width = frame.child("rect").attribute("width").as_int();
                rect.height = frame.child("rect").attribute("height").as_int();

                origin.x = frame.child("origin").attribute("x").as_int();
                origin.y = frame.child("origin").attribute("y").as_int();

                animSPtr->addFrame(Animation::Frame(rect, origin));
            }

            mAnimations.emplace_back(type, dir, animSPtr);
        }
    }

    return true;
}

bool Entity::loadFromFile(std::string filename)
{
    pugi::xml_document doc;
    if (!doc.load_file(filename.c_str()))
        return false;

    return loadFromNode(doc.child("entity"));
}

void Entity::setAnimation(Animations::Type type)
{
    mCurAnim = type;
    restart();
}

void Entity::setFacing(Direction::Dir facing)
{
    mFacing = facing;
    restart();
}

void Entity::setAnimationAndFacing(Animations::Type anim, Direction::Dir facing)
{
    mCurAnim = anim;
    mFacing = facing;
    restart();
}

Direction::Dir Entity::getFacing() const
{
    return mFacing;
}

void Entity::restart()
{
    auto it = std::find_if(mAnimations.begin(), mAnimations.end(), [this](AnimStruct as) { return as.type == mCurAnim && as.facing == mFacing; });
    assert(it != mAnimations.end());
    it->anim->restart();
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    auto it = std::find_if(mAnimations.begin(), mAnimations.end(), [this](AnimStruct as) { return as.type == mCurAnim && as.facing == mFacing; });
    assert(it != mAnimations.end());
    target.draw(*(it->anim), states);
}

void Entity::update(sf::Time delta)
{
    auto it = std::find_if(mAnimations.begin(), mAnimations.end(), [this](AnimStruct as) { return as.type == mCurAnim && as.facing == mFacing; });
    assert(it != mAnimations.end());
    it->anim->update(delta);
}

bool Entity::isAnimationFinished() const
{
    auto it = std::find_if(mAnimations.begin(), mAnimations.end(), [this](AnimStruct as) { return as.type == mCurAnim && as.facing == mFacing; });
    assert(it != mAnimations.end());
    return it->anim->isFinished();
}

}
