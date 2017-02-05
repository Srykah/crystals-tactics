#include "../Gameplay/Battlefield.hpp"
#include "../Other/pugixml.hpp"
#include "../Other/ResourceHolder.hpp"
#include "../Graphism/Colors.hpp"
#include "../Gameplay/UnitList.hpp"
#include "../Gameplay/Character.hpp"
#include "../Graphism/Animation.hpp"
#include <stdexcept>
#include <sstream>


Battlefield::Tile::Tile(int left, int top, bool wall)
: wall(wall)
, topLeft(left, top)
, topRight(left+TILE_DIM, top)
, bottomLeft(left, top+TILE_DIM)
, bottomRight(left+TILE_DIM, top+TILE_DIM)
{

}


Battlefield::Paint::Paint(bool spawn, bool highlight, bool selection)
: spawn(spawn)
, highlight(highlight)
, selection(selection)
{

}



Battlefield::Battlefield(EntityHolder* entityHolder, UnitList* unitList)
: mTransparentTile(0)
, mUnitList(unitList)
, mCursorBack(entityHolder->get(Entities::BattlefieldCursorBack))
, mCursorFront(entityHolder->get(Entities::BattlefieldCursorFront))
, mCursorCoords(0,0)
, mShowCursor(false)
, mBackground(sf::Quads, 0)
, mForeground(sf::Quads, 0)
, mShowSpawns(false)
{
    mCursorBack.setAnimation(Graphism::Animations::Idle);
    mCursorBack.setFacing(Direction::Down);
    mCursorBack.move(float(TILE_DIM)*sf::Vector2f(0.5,0.5));
    mCursorFront.setAnimation(Graphism::Animations::Idle);
    mCursorFront.setFacing(Direction::Down);
    mCursorFront.move(float(TILE_DIM)*sf::Vector2f(0.5,0.5));
}

Battlefield::~Battlefield()
{

}

void Battlefield::loadFromFile(std::string file)
{
    ///ouverture du fichier
    pugi::xml_document doc;
    if(!doc.load_file(file.c_str()))
        throw std::runtime_error("Couldn't open battlefield script");

    const pugi::xml_node& tilesNode = doc.child("tiles");
    const pugi::xml_node& battlefieldNode = doc.child("battlefield");
    const pugi::xml_node& foregroundNode = doc.child("foreground");
    const pugi::xml_node& spawnsNode = doc.child("spawns");

    ///lecture des infos sur les tuiles
    mTileSheet.loadFromFile(tilesNode.attribute("tileSheet").as_string());

    for (const pugi::xml_node& tile : tilesNode)
    {
        if (std::string(tile.name()) == std::string("tile"))
        {
            char c = tile.attribute("letter").as_string()[0];
            int left = tile.attribute("left").as_uint();
            int top = tile.attribute("top").as_uint();
            bool wall = tile.attribute("wall").as_bool();

            mTiles[c] = Tile(left, top, wall);
        }
        else if (std::string(tile.name()) == std::string("transparent"))
            mTransparentTile = tile.attribute("letter").as_string()[0];
    }

    ///lecture des infos sur la grille de combat (sens de lecture)

    //récupération de la taille de la grille
    int battlefieldWidth = battlefieldNode.attribute("width").as_uint();
    int battlefieldHeight = battlefieldNode.attribute("height").as_uint();

    //récupération des caractères qui composent la grille de combat
    std::istringstream iss(battlefieldNode.text().as_string());

    mTileGrid.resize(battlefieldHeight);
    mPaintGrid.resize(battlefieldHeight);
    for (int i(0); i < battlefieldHeight; i++)
    {
        mPaintGrid[i].resize(battlefieldWidth);
        for (int j(0); j < battlefieldWidth; j++)
        {
            char c;
            iss >> c;
            mTileGrid[i].push_back(c);

            if (c != mTransparentTile)
            {
                sf::Vector2f corner(j*TILE_DIM, i*TILE_DIM);
                const Tile& tile(mTiles.at(c));

                //sens des aiguilles d'une montre en commençant par haut-gauche
                mBackground.append(sf::Vertex(corner, tile.topLeft));
                mBackground.append(sf::Vertex(corner+sf::Vector2f(TILE_DIM,0), tile.topRight));
                mBackground.append(sf::Vertex(corner+sf::Vector2f(TILE_DIM,TILE_DIM), tile.bottomRight));
                mBackground.append(sf::Vertex(corner+sf::Vector2f(0,TILE_DIM), tile.bottomLeft));
            }
        }
    }

    ///récupération du décor
    if (!foregroundNode.empty())
    {
        std::istringstream iss2(foregroundNode.text().as_string());

        for (int i(0); i < battlefieldHeight; i++)
        {
            for (int j(0); j < battlefieldWidth; j++)
            {
                char c;
                iss2 >> c;
                if (c != mTransparentTile)
                {
                    const Tile& tile(mTiles.at(c));

                    sf::Vector2f corner(j*TILE_DIM, i*TILE_DIM);

                    //sens des aiguilles d'une montre en commençant par haut-gauche
                    mForeground.append(sf::Vertex(corner, tile.topLeft));
                    mForeground.append(sf::Vertex(corner+sf::Vector2f(TILE_DIM,0), tile.topRight));
                    mForeground.append(sf::Vertex(corner+sf::Vector2f(TILE_DIM,TILE_DIM), tile.bottomRight));
                    mForeground.append(sf::Vertex(corner+sf::Vector2f(0,TILE_DIM), tile.bottomLeft));
                }
            }
        }
    }

    ///récupération des spawns
    for(auto spawn : spawnsNode)
    {
        int x(spawn.attribute("x").as_uint()), y(spawn.attribute("y").as_uint());
        mSpawns.emplace_back(x,y);
        mPaintGrid[y][x].spawn = true;
    }

}

void Battlefield::update(sf::Time delta)
{
    mCursorBack.update(delta);
    mCursorFront.update(delta);
}

void Battlefield::handleInput(const sf::Event& event, IH::SA stdAc, sf::Vector2f mousePos)
{
    if (stdAc == IH::Down && getCursorCoords().y < getGridSize().y-1)
    {
        mCursorCoords.y++;
        mCursorBack.move(0,float(TILE_DIM));
        mCursorFront.move(0,float(TILE_DIM));
    }
    else if (stdAc == IH::Right && getCursorCoords().x < getGridSize().x-1)
    {
        mCursorCoords.x++;
        mCursorBack.move(float(TILE_DIM),0);
        mCursorFront.move(float(TILE_DIM),0);
    }
    else if (stdAc == IH::Up && getCursorCoords().y > 0)
    {
        mCursorCoords.y--;
        mCursorBack.move(0,-float(TILE_DIM));
        mCursorFront.move(0,-float(TILE_DIM));

    }
    else if (stdAc == IH::Left && getCursorCoords().x > 0)
    {
        mCursorCoords.x--;
        mCursorBack.move(-float(TILE_DIM),0);
        mCursorFront.move(-float(TILE_DIM),0);
    }
}

void Battlefield::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //draw background first
    sf::RenderStates gridStates(states);
    gridStates.texture = &mTileSheet;
    target.draw(mBackground, gridStates);

    //then the back of the cursor
    if (mShowCursor)
        target.draw(mCursorBack, states);

    //then the characters
    for (auto& _pair : *mUnitList)
    {
        //warning : units must be sorted in order of draw inside unitlist
        Character& character = *_pair.second;
        target.draw(character, states);
    }

    //then the foreground
    target.draw(mForeground, gridStates);

    //then the front of the cursor
    if (mShowCursor)
        target.draw(mCursorFront, states);
}

sf::Vector2i Battlefield::getGridSize() const
{
    return sf::Vector2i(mTileGrid[0].size(), mTileGrid.size());
}

bool Battlefield::isWall(sf::Vector2i tile) const
{
    char c(mTileGrid[tile.y][tile.x]);
    if (c == mTransparentTile)
        return false;
    else
        return mTiles.at(c).wall;
}

sf::Vector2i Battlefield::getCursorCoords() const
{
    return mCursorCoords;
}

void Battlefield::setCursorCoords(sf::Vector2i tile)
{
    mCursorCoords = tile;
    mCursorBack.setPosition(TILE_DIM*(tile.x+0.5), TILE_DIM*(tile.y+0.5));
    mCursorFront.setPosition(TILE_DIM*(tile.x+0.5), TILE_DIM*(tile.y+0.5));
}

sf::Vector2f Battlefield::getCursorPosition() const
{
    return mCursorBack.getPosition();
}

void Battlefield::showCursor(bool flag)
{
    mShowCursor = flag;
}

/** ordre de peinture :
 *   1- sélection
 *   2- spawn
 *   3- surlignage
 *
 *  note : la cohérence est assez faible avec les spawns, mais de toute façon ils seront gérés
 *  grâce au curseur sans mélange avec d'autres types de peinture.
 */

void Battlefield::setTileHighlight(sf::Vector2i tile)
{
    Paint& paint(mPaintGrid[tile.y][tile.x]);

    if (!paint.highlight)
    {
        paint.highlight = true;

        // si la case n'est ni sélectionnée ni affichée en tant que spawn
        if (!paint.selection && !(paint.spawn && mShowSpawns))
        {
            //on la met en bleu transparent
            int w(mTileGrid[0].size());

            mBackground[4*(tile.y*w+tile.x)].color = Colors::LightBlue;
            mBackground[4*(tile.y*w+tile.x)+1].color = Colors::LightBlue;
            mBackground[4*(tile.y*w+tile.x)+2].color = Colors::LightBlue;
            mBackground[4*(tile.y*w+tile.x)+3].color = Colors::LightBlue;
        }
    }
}

void Battlefield::setZoneHighlight(std::vector<sf::Vector2i> zone)
{
    for (sf::Vector2i tile : zone)
        setTileHighlight(tile);
}

bool Battlefield::isHighlighted(sf::Vector2i tile) const
{
    return mPaintGrid[tile.y][tile.x].highlight;
}

void Battlefield::clearHighlight()
{
    int w(mTileGrid[0].size()), h(mTileGrid.size());

    for (int i(0); i < h; i++)
    {
        for (int j(0); j < w; j++)
        {
            //reset highlight
            Paint& paint(mPaintGrid[i][j]);
            paint.highlight = false;

            //if the tile isn't selected nor shown as spawn, paint it back to white
            if (!paint.selection && !(paint.spawn && mShowSpawns))
            {
                mBackground[4*(i*w+j)].color = sf::Color::White;
                mBackground[4*(i*w+j)+1].color = sf::Color::White;
                mBackground[4*(i*w+j)+2].color = sf::Color::White;
                mBackground[4*(i*w+j)+3].color = sf::Color::White;
            }
        }
    }
}

void Battlefield::setTileSelection(sf::Vector2i tile)
{
    Paint& paint(mPaintGrid[tile.y][tile.x]);

    if (!paint.selection)
    {
        paint.selection = true;

        // si la case est sélectionnée, on la met en jaune transparent
        int w(mTileGrid[0].size());

        mBackground[4*(tile.y*w+tile.x)].color = Colors::RareGrey;
        mBackground[4*(tile.y*w+tile.x)+1].color = Colors::RareGrey;
        mBackground[4*(tile.y*w+tile.x)+2].color = Colors::RareGrey;
        mBackground[4*(tile.y*w+tile.x)+3].color = Colors::RareGrey;
    }
}

void Battlefield::setZoneSelection(std::vector<sf::Vector2i> zone)
{
    for (sf::Vector2i tile : zone)
        setTileSelection(tile);
}

void Battlefield::clearSelection()
{
    int w(mTileGrid[0].size()), h(mTileGrid.size());

    for (int i(0); i < h; i++)
    {
        for (int j(0); j < w; j++)
        {
            //reset selection
            Paint& paint(mPaintGrid[i][j]);
            paint.selection = false;

            //if the tile is shown as spawn, paint it in green
            if (paint.spawn && mShowSpawns)
            {
                mBackground[4*(i*w+j)].color = Colors::LightGreen;
                mBackground[4*(i*w+j)+1].color = Colors::LightGreen;
                mBackground[4*(i*w+j)+2].color = Colors::LightGreen;
                mBackground[4*(i*w+j)+3].color = Colors::LightGreen;
            }
            //else if it is highlighted, paint it in blue
            else if (paint.highlight)
            {
                mBackground[4*(i*w+j)].color = Colors::LightBlue;
                mBackground[4*(i*w+j)+1].color = Colors::LightBlue;
                mBackground[4*(i*w+j)+2].color = Colors::LightBlue;
                mBackground[4*(i*w+j)+3].color = Colors::LightBlue;
            }
            //else paint it back to white
            else
            {
                mBackground[4*(i*w+j)].color = sf::Color::White;
                mBackground[4*(i*w+j)+1].color = sf::Color::White;
                mBackground[4*(i*w+j)+2].color = sf::Color::White;
                mBackground[4*(i*w+j)+3].color = sf::Color::White;
            }
        }
    }
}

bool Battlefield::isSpawn(sf::Vector2i tile) const
{
    return mPaintGrid[tile.y][tile.x].spawn;
}

void Battlefield::showSpawns(bool flag)
{
    if (mShowSpawns != flag)
    {
        mShowSpawns = flag;

        // if we have to show them and they're not selected, paint them in green
        if (mShowSpawns)
        {
            int w(mTileGrid[0].size());

            for (sf::Vector2i s : mSpawns)
            {
                if (!mPaintGrid[s.y][s.x].selection)
                {
                    mBackground[4*(s.y*w+s.x)].color = Colors::LightGreen;
                    mBackground[4*(s.y*w+s.x)+1].color = Colors::LightGreen;
                    mBackground[4*(s.y*w+s.x)+2].color = Colors::LightGreen;
                    mBackground[4*(s.y*w+s.x)+3].color = Colors::LightGreen;
                }
            }
        }
        else //if we want to turn off the spawns
        {
            int w(mTileGrid[0].size());

            for (sf::Vector2i s : mSpawns)
            {
                //if they are not selected but they are highlighted, paint them in blue
                if (!mPaintGrid[s.y][s.x].selection && mPaintGrid[s.y][s.x].highlight)
                {
                    mBackground[4*(s.y*w+s.x)].color = Colors::LightBlue;
                    mBackground[4*(s.y*w+s.x)+1].color = Colors::LightBlue;
                    mBackground[4*(s.y*w+s.x)+2].color = Colors::LightBlue;
                    mBackground[4*(s.y*w+s.x)+3].color = Colors::LightBlue;
                }
                //if they are not selected nor highligted, paint them back in white
                else if (!mPaintGrid[s.y][s.x].selection && !mPaintGrid[s.y][s.x].highlight)
                {
                    mBackground[4*(s.y*w+s.x)].color = sf::Color::White;
                    mBackground[4*(s.y*w+s.x)+1].color = sf::Color::White;
                    mBackground[4*(s.y*w+s.x)+2].color = sf::Color::White;
                    mBackground[4*(s.y*w+s.x)+3].color = sf::Color::White;
                }
            }
        }
    }
}

void Battlefield::clearPaint()
{
    mShowSpawns = false;

    //paint everything back in white
    for (unsigned int i(0); i < mBackground.getVertexCount(); i++)
        mBackground[i].color = sf::Color::White;

    //and indicate that everything is turned off
    int w(mTileGrid[0].size()), h(mTileGrid.size());

    for (int i(0); i < h; i++)
    {
        for (int j(0); j < w; j++)
        {
            mPaintGrid[i][j].selection = false;
            mPaintGrid[i][j].highlight = false;
        }
    }
}
