#include "Gameplay/Battle/Battlefield.hpp"
#include "XML/pugixml.hpp"
#include "Data/ResourceHolder/ResourceHolder.hpp"
#include "Graphism/Colors.hpp"
#include "Graphism/HUD/Cursor.hpp"
#include "Graphism/Scene/Scene.hpp"
#include "Graphism/Scene/NoOwnNode.hpp"
#include "Graphism/Scene/EntityNode.hpp"
#include <stdexcept>
#include <sstream>

namespace
{
    const sf::Vector2f right(TILE_DIM,0), down(0,TILE_DIM);
}

namespace bt
{

Battlefield::Battlefield()
: mNoTileID(0)
, mTerrain(sf::Quads, 0)
{

}

Battlefield::~Battlefield()
{

}

void Battlefield::loadFromFile(const sf::String& file, gr::Scene& scene,
                               dt::EntityHolder* entityHolder, gr::Cursor& cursor)
{
    ///ouverture du fichier
    pugi::xml_document doc;
    if(!doc.load_file(file.toAnsiString().c_str()))
        throw std::runtime_error("Couldn't open battlefield script");

    const pugi::xml_node& tilesNode = doc.child("tiles");
    const pugi::xml_node& battlefieldNode = doc.child("battlefield");
    const pugi::xml_node& decorationsNode = doc.child("decorations");
    const pugi::xml_node& spawnsNode = doc.child("spawns");
    const pugi::xml_node& cursorNode = doc.child("cursor");

    ///lecture des infos sur les tuiles
    mTileSheet.loadFromFile(tilesNode.attribute("tileSheet").as_string());
    mNoTileID = tilesNode.attribute("noTileID").as_string()[0];

    for (const pugi::xml_node& tile : tilesNode)
    {
        char c = tile.attribute("letter").as_string()[0];
        sf::Vector2u texCoords(tile.attribute("x").as_uint(), tile.attribute("y").as_uint());
        bool walkable = tile.attribute("walkable").as_bool();
        bool blocking = tile.attribute("blocking").as_bool();

        mTileProps.emplace(std::make_pair(c, TileProps(texCoords, walkable, blocking)));
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

            if (c != mNoTileID)
            {
                sf::Vector2f corner(j*TILE_DIM, i*TILE_DIM);
                const sf::Vector2f texCoords(mTileProps.at(c).texCoords);

                //sens des aiguilles d'une montre en commençant par haut-gauche
                mTerrain.append(sf::Vertex(corner, texCoords));
                mTerrain.append(sf::Vertex(corner+right, texCoords+right));
                mTerrain.append(sf::Vertex(corner+down+right, texCoords+down+right));
                mTerrain.append(sf::Vertex(corner+down, texCoords+down));
            }
        }
    }

    //ajout à la scène
    scene.addNode(new gr::NoOwnNode(this, 0.f));

    ///récupération des décorations, à ajouter à la scène en tant qu'enfant de la node du champ de bataille

    ///récupération des spawns
    for(auto spawn : spawnsNode)
        mSpawns.emplace_back(spawn.attribute("x").as_uint(), spawn.attribute("y").as_uint());

    ///initialisation du curseur
    sf::Vector2i cursorCoords(cursorNode.attribute("x").as_uint(), cursorNode.attribute("y").as_uint());
    cursor.setCoords(cursorCoords);
}

void Battlefield::update(sf::Time delta)
{
    for (gr::Entity& decoration : mDecorations)
        decoration.update(delta);
}

void Battlefield::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RenderStates gridStates(states);
    gridStates.texture = &mTileSheet;
    target.draw(mTerrain, gridStates);
}

sf::Vector2i Battlefield::getGridSize() const
{
    return sf::Vector2i(mTileGrid[0].size(), mTileGrid.size());
}

bool Battlefield::contains(sf::Vector2i tile) const
{
    return sf::IntRect(sf::Vector2i(), getGridSize()).contains(tile);
}

Battlefield::TileProps Battlefield::getProps(sf::Vector2i tile) const
{
    char c(mTileGrid[tile.y][tile.x]);
    if (c == mNoTileID)
        return TileProps();
    else
        return mTileProps.at(c);
}

/// note : l'affichage de la sélection est prioritaire sur le surlignage.

void Battlefield::highlightTile(sf::Vector2i tile)
{
    Paint& paint(mPaintGrid[tile.y][tile.x]);

    if (!paint.highlight)
    {
        paint.highlight = true;

        if (!paint.selection) // si la case n'est pas sélectionnée, on la met en bleu transparent
        {
            int w(mTileGrid[0].size());

            mTerrain[4*(tile.y*w+tile.x)].color = Colors::LightBlue;
            mTerrain[4*(tile.y*w+tile.x)+1].color = Colors::LightBlue;
            mTerrain[4*(tile.y*w+tile.x)+2].color = Colors::LightBlue;
            mTerrain[4*(tile.y*w+tile.x)+3].color = Colors::LightBlue;
        }
    }
}

void Battlefield::highlightZone(std::vector<sf::Vector2i> zone)
{
    for (sf::Vector2i tile : zone)
        highlightTile(tile);
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
            Paint& paint(mPaintGrid[i][j]);

            paint.highlight = false; //reset highlight

            if (!paint.selection) //if the tile is not selected, paint it back to white
            {
                mTerrain[4*(i*w+j)].color = sf::Color::White;
                mTerrain[4*(i*w+j)+1].color = sf::Color::White;
                mTerrain[4*(i*w+j)+2].color = sf::Color::White;
                mTerrain[4*(i*w+j)+3].color = sf::Color::White;
            }
        }
    }
}

void Battlefield::selectTile(sf::Vector2i tile)
{
    Paint& paint(mPaintGrid[tile.y][tile.x]);
    int w(mTileGrid[0].size());

    if (!paint.selection)
    {
        paint.selection = true;

        // on peint la case sélectionnée en gris
        mTerrain[4*(tile.y*w+tile.x)].color = Colors::RareGrey;
        mTerrain[4*(tile.y*w+tile.x)+1].color = Colors::RareGrey;
        mTerrain[4*(tile.y*w+tile.x)+2].color = Colors::RareGrey;
        mTerrain[4*(tile.y*w+tile.x)+3].color = Colors::RareGrey;
    }
}

void Battlefield::selectZone(std::vector<sf::Vector2i> zone)
{
    for (sf::Vector2i tile : zone)
        selectTile(tile);
}

void Battlefield::clearSelection()
{
    int w(mTileGrid[0].size()), h(mTileGrid.size());

    for (int i(0); i < h; i++)
    {
        for (int j(0); j < w; j++)
        {
            Paint& paint(mPaintGrid[i][j]);
            paint.selection = false; //reset selection

            if (paint.highlight) //if it is highlighted, paint it back to blue
            {
                mTerrain[4*(i*w+j)].color = Colors::LightBlue;
                mTerrain[4*(i*w+j)+1].color = Colors::LightBlue;
                mTerrain[4*(i*w+j)+2].color = Colors::LightBlue;
                mTerrain[4*(i*w+j)+3].color = Colors::LightBlue;
            }
            else //else paint it back to white
            {
                mTerrain[4*(i*w+j)].color = sf::Color::White;
                mTerrain[4*(i*w+j)+1].color = sf::Color::White;
                mTerrain[4*(i*w+j)+2].color = sf::Color::White;
                mTerrain[4*(i*w+j)+3].color = sf::Color::White;
            }
        }
    }
}

bool Battlefield::isSpawn(sf::Vector2i tile) const
{
    return std::find(mSpawns.begin(), mSpawns.end(), tile) != mSpawns.end();
}

void Battlefield::highlightSpawns()
{
    for (sf::Vector2i spawn : mSpawns)
        highlightTile(spawn);
}

void Battlefield::clearPaint()
{
    clearHighlight();
    clearSelection();
}

}
