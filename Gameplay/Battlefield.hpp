#ifndef BATTLEFIELD_HPP_INCLUDED
#define BATTLEFIELD_HPP_INCLUDED

#include "../Other/ResourceIdentifiers.hpp"
#include "../Input/InputHandler.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>

class UnitList;

template<typename T>
using Grid = std::vector< std::vector< T > >;

const int TILE_DIM(32);



class Battlefield : public sf::Drawable
{
public:
                    Battlefield(EntityHolder* entityHolder, UnitList* unitList); //ok
                    ~Battlefield();

    void            loadFromFile(std::string file); //ok

    virtual void    update(sf::Time delta); //ok
    virtual void    handleInput(const sf::Event& event, IH::SA stdAction, sf::Vector2f mousePos); //pas fini
    virtual void    draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const; //ok

    sf::Vector2i    getGridSize() const; //ok
    bool            isWall(sf::Vector2i tile) const;

    sf::Vector2i    getCursorCoords() const; //ok
    void            setCursorCoords(sf::Vector2i tile);
    sf::Vector2f    getCursorPosition() const; //ok
    void            showCursor(bool flag = true);

    void            setTileHighlight(sf::Vector2i tile); //ok
    void            setZoneHighlight(std::vector<sf::Vector2i> zone); //ok
    bool            isHighlighted(sf::Vector2i tile) const; //ok
    void            clearHighlight();

    void            setTileSelection(sf::Vector2i tile); //ok
    void            setZoneSelection(std::vector<sf::Vector2i> zone); //ok
    void            clearSelection();

    bool            isSpawn(sf::Vector2i tile) const;
    void            showSpawns(bool flag = true); //ok

    void            clearPaint();

private:
    struct Tile
    {
        Tile(int left = 0, int top = 0, bool wall = false); //ok

        bool wall;
        sf::Vector2f topLeft, topRight, bottomLeft, bottomRight;
    };

    struct Paint
    {
        Paint(bool spawn = false, bool highlight = false, bool selection = false);

        bool spawn, highlight, selection;
    };

private:
    std::map< char, Tile >          mTiles;
    char                            mTransparentTile;
    Grid< char >                    mTileGrid;
    Grid< Paint >                   mPaintGrid;
    UnitList*                       mUnitList;

    Graphism::Entity                mCursorBack;
    Graphism::Entity                mCursorFront;
    sf::Vector2i                    mCursorCoords;
    bool                            mShowCursor;

    sf::Texture                     mTileSheet;
    sf::VertexArray                 mBackground;
    sf::VertexArray                 mForeground;
    bool                            mShowSpawns;

    std::vector< sf::Vector2i >     mHighlightedTiles;
    std::vector< sf::Vector2i >     mSelectedTiles;
    std::vector< sf::Vector2i >     mSpawns;
};

#endif // BATTLEFIELD_HPP_INCLUDED
