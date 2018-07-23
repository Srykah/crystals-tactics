#ifndef BATTLEFIELD_HPP_INCLUDED
#define BATTLEFIELD_HPP_INCLUDED

#include "Data/DataIdentifiers.hpp"
#include "Input/Listener.hpp"
#include "Graphism/Entity/Entity.hpp"
#include "Gameplay/General/Routines.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include <vector>
#include <map>

class UnitList;
namespace gr
{
    class Scene;
    class Cursor;
}

namespace bt
{

class Battlefield : public sf::Drawable
{
public:
    struct TileProps
    {
        TileProps(sf::Vector2u texCoords = sf::Vector2u(), bool walkable = true, bool blocking = false) :
            texCoords(texCoords), walkable(walkable), blocking(blocking) {}

        sf::Vector2u texCoords;
        bool walkable, blocking;
    };

public:
                    Battlefield();
                    ~Battlefield();

    void            loadFromFile(const sf::String& file, gr::Scene& scene,
                                 dt::EntityHolder* entityHolder, gr::Cursor& cursor);

    virtual void    update(sf::Time delta);
    virtual void    draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;

    sf::Vector2i    getGridSize() const;
    bool            contains(sf::Vector2i tile) const;
    TileProps       getProps(sf::Vector2i tile) const;

    void            highlightTile(sf::Vector2i tile);
    void            highlightZone(std::vector<sf::Vector2i> zone);
    bool            isHighlighted(sf::Vector2i tile) const;
    void            clearHighlight();

    void            selectTile(sf::Vector2i tile);
    void            selectZone(std::vector<sf::Vector2i> zone);
    void            clearSelection();

    void            highlightSpawns();
    bool            isSpawn(sf::Vector2i tile) const;

    void            clearPaint();

private:
    struct Paint
    {
        Paint(bool highlight = false, bool selection = false) :
            highlight(highlight), selection(selection) {}

        bool highlight, selection;
    };

private:
    std::map< char, TileProps >     mTileProps;
    char                            mNoTileID;
    Grid< char >                    mTileGrid;
    Grid< Paint >                   mPaintGrid;
    std::vector< sf::Vector2i >     mSpawns;

    sf::Texture                     mTileSheet;
    sf::VertexArray                 mTerrain;
    std::vector< gr::Entity > mDecorations;
};

}

#endif // BATTLEFIELD_HPP_INCLUDED
