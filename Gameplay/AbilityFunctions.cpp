#include "../Gameplay/AbilityFunctions.hpp"
#include "../Gameplay/Character.hpp"
#include "../Gameplay/UnitList.hpp"
#include "../Gameplay/Battlefield.hpp"
#include "../Other/Utility.hpp"
#include "../Gameplay/Weapon.hpp"

namespace Ab
{

bool isVisible(const Character* user, sf::Vector2i tile) // to rewrite
{
    if (tile.x >= 0 && tile.y >=0
        && tile.x < user->getBattlefield()->getGridSize().x && tile.y < user->getBattlefield()->getGridSize().y)
        return false;

    sf::Vector2f c(user->getCoords());
    sf::Vector2f line(sf::Vector2f(tile)-c);
    c += sf::Vector2f(0.5, 0.5);
    sf::Vector2f u(unitVector(line));

    for (float t(0.8); t < length(line); t += 0.3)
    {
        sf::Vector2i currentTile(c+t*u);

        if (user->getBattlefield()->isWall(currentTile)
            || (currentTile != tile and user->getUnitList()->getUnitByTile(currentTile) != nullptr))
            return false;
    }

    return true;
}

std::vector<sf::Vector2i> getCircleRange(const Character* user, int min, int max)
{
    std::vector<sf::Vector2i> tiles;
    sf::Vector2i c(user->getCoords());

    // si la portée min est 0, on inclut la case du lanceur
    tiles.push_back(c);
    // on parcourt la grille par carrés concentriques de rayon croissant
    for (int rayon = (min >= 1 ? min : 1); rayon <= max; rayon++)
    {
        for (int diagonale = 0; diagonale < rayon; diagonale++)
        {
            // on parcourt chaque carré selon ses 4 diagonales (sens horaire, origine en haut)

            // diagonale sens bas-droit (du nord à l'est)
            sf::Vector2i ne(c.x+diagonale, c.y-rayon+diagonale)
            if (isVisible(user, ne))
                tiles.push_back(ne);

            // diagonale sens bas-gauche (de l'est au sud)
            sf::Vector2i se(c.x+rayon-diagonale, c.y+diagonale)
            if (isVisible(user, se))
                tiles.push_back(se);

            // diagonale sens haut-gauche (du sud à l'ouest)
            sf::Vector2i sw(c.x-diagonale, c.y+rayon-diagonale)
            if (isVisible(user, sw))
                tiles.push_back(sw);

            // diagonale sens haut-droit (de l'ouest au nord)
            sf::Vector2i nw(c.x-rayon+diagonale, c.y-diagonale)
            if (isVisible(user, nw))
                tiles.push_back(nw);
        }
    }

    return tiles;
}

std::vector<sf::Vector2i> getSquareRange(const Character* user, int min, int max)
{
    std::vector<sf::Vector2i> tiles;
    sf::Vector2i c(user->getCoords());

    // si la portée min est 0, on inclut la case du lanceur
    tiles.push_back(c);
    // on parcourt la grille par carrés concentriques de rayon croissant
    for (int rayon = (min >= 1 ? min : 1); rayon <= max; rayon++)
    {
        for (int cote = 0; cote < 2*rayon; cote++)
        {
            // on parcourt chaque carré selon ses 4 côtés (sens horaire, origine en haut à droite)

            // côté haut (vers la gauche)
            sf::Vector2i up(c.x-rayon+cote, c.y-rayon)
            if (isVisible(user, up))
                tiles.push_back(up);

            // côté droit (vers le bas)
            sf::Vector2i right(c.x+rayon, c.y-rayon+cote)
            if (isVisible(user, right))
                tiles.push_back(right);

            // côté bas (vers la droite)
            sf::Vector2i down(c.x+rayon-cote, c.y+rayon)
            if (isVisible(user, down))
                tiles.push_back(down);

            // côté gauche (vers le haut)
            sf::Vector2i left(c.x-rayon, c.y+rayon-cote)
            if (isVisible(user, left))
                tiles.push_back(left);
        }
    }

    return tiles;
}

std::vector<sf::Vector2i> getCrossRange(const Character* user, int min, int max)
{
    std::vector<sf::Vector2i> tiles;
    sf::Vector2i c(user->getCoords());

    // si la portée min est 0, on inclut la case du lanceur
    tiles.push_back(c);
    // on parcourt la grille par lignes pour chaque direction
    for (int decal = (min >= 1 ? min : 1); decal <= max; decal++)
    {
        // côté haut
        sf::Vector2i up(c.x, c.y-decal)
        if (isVisible(user, up))
            tiles.push_back(up);

        // côté droit
        sf::Vector2i right(c.x+decal, c.y)
        if (isVisible(user, right))
            tiles.push_back(right);

        // côté bas
        sf::Vector2i down(c.x, c.y+decal)
        if (isVisible(user, down))
            tiles.push_back(down));

        // côté gauche
        sf::Vector2i left(c.x-decal, c.y)
        if (isVisible(user, left))
            tiles.push_back(left);
    }

    return tiles;
}

std::vector<sf::Vector2i> getCircleArea(sf::Vector2i tile, int min, int max, const Battlefield* bf)
{
    std::vector<sf::Vector2i> tiles;
    sf::Vector2i s(bf->getGridSize());

    // si la portée min est 0, on inclut la case visée
    tiles.push_back(tile);
    // on parcourt la grille par carrés concentriques de rayon croissant
    for (int rayon = (min >= 1 ? min : 1); rayon <= max; rayon++)
    {
        for (int diagonale = 0; diagonale < rayon; diagonale++)
        {
            // on parcourt chaque carré selon ses 4 diagonales (sens horaire, origine en haut)

            // diagonale sens bas-droit (du nord à l'est)
            sf::Vector2i ne(tile.x+diagonale, tile.y-rayon+diagonale);
            if (ne.x >= 0 && ne.y >=0 && ne.x < s.x && ne.y < s.y && !bf->isWall(ne))
                tiles.push_back(ne);

            // diagonale sens bas-gauche (de l'est au sud)
            sf::Vector2i se(tile.x+rayon-diagonale, tile.y+diagonale)
            if (se.x >= 0 && se.y >=0 && se.x < s.x && se.y < s.y && !bf->isWall(se))
                tiles.push_back(se);

            // diagonale sens haut-gauche (du sud à l'ouest)
            sf::Vector2i sw(tile.x-diagonale, tile.y+rayon-diagonale)
            if (sw.x >= 0 && sw.y >=0 && sw.x < s.x && sw.y < s.y && !bf->isWall(sw))
                tiles.push_back(sw);

            // diagonale sens haut-droit (de l'ouest au nord)
            sf::Vector2i nw(tile.x-rayon+diagonale, tile.y-diagonale)
            if (nw.x >= 0 && nw.y >=0 && nw.x < s.x && nw.y < s.y && !bf->isWall(nw))
                tiles.push_back(nw);
        }
    }

    return tiles;
}

std::vector<sf::Vector2i> getSquareArea(sf::Vector2i tile, int min, int max, const Battlefield* bf)
{
    std::vector<sf::Vector2i> tiles;
    sf::Vector2i s(bf->getGridSize());

    // si la portée min est 0, on inclut la case du lanceur
    tiles.push_back(tile);
    // on parcourt la grille par carrés concentriques de rayon croissant
    for (int rayon = (min >= 1 ? min : 1); rayon <= max; rayon++)
    {
        for (int cote = 0; cote < 2*rayon; cote++)
        {
            // on parcourt chaque carré selon ses 4 côtés (sens horaire, origine en haut à droite)

            // côté haut (vers la gauche)
            sf::Vector2i up(tile.x-rayon+cote, tile.y-rayon);
            if (up.x >= 0 && up.y >=0 && up.x < s.x && up.y < s.y && !bf->isWall(up))
                tiles.push_back(up);

            // côté droit (vers le bas)
            sf::Vector2i right(tile.x+rayon, tile.y-rayon+cote);
            if (right.x >= 0 && right.y >=0 && right.x < s.x && right.y < s.y && !bf->isWall(right))
                tiles.push_back(right);

            // côté bas (vers la droite)
            sf::Vector2i down(tile.x+rayon-cote, tile.y+rayon)
            if (down.x >= 0 && down.y >=0 && down.x < s.x && down.y < s.y && !bf->isWall(down))
                tiles.push_back(down);

            // côté gauche (vers le haut)
            sf::Vector2i left(tile.x-rayon, tile.y+rayon-cote)
            if (left.x >= 0 && left.y >=0 && left.x < s.x && right.y < s.y
                && !bf->isWall(left))
                tiles.push_back(left);
        }
    }

    return tiles;
}

std::vector<sf::Vector2i> getCrossArea(sf::Vector2i tile, int min, int max, const Battlefield* bf)
{
    std::vector<sf::Vector2i> tiles;
    sf::Vector2i s(bf->getGridSize());

    // si la portée min est 0, on inclut la case du lanceur
    tiles.push_back(c);
    // on parcourt la grille par lignes pour chaque direction
    for (int decal = (min >= 1 ? min : 1); decal <= max; decal++)
    {
        // haut
        sf::Vector2i up(tile.x, tile.y-decal);
        if (up.x >= 0 && up.y >= 0 && up.x < s.x && up.y < s.y && !bf->isWall(up))
            tile.push_back(up);

        // droite
        sf::Vector2i right(tile.x+decal, tile.y);
        if (right.x >= 0 && right.y >= 0 && right.x < s.x && right.y < s.y && !bf->isWall(right))
            tile.push_back(right);

        // bas
        sf::Vector2i down(tile.x, tile.y+decal);
        if (down.x >= 0 && down.y >= 0 && down.x < s.x && down.y < s.y && !bf->isWall(down))
            tile.push_back(down);

        // gauche
        sf::Vector2i left(tile.x, tile.y-decal);
        if (left.x >= 0 && left.y >= 0 && left.x < s.x && left.y < s.y && !bf->isWall(left))
            tile.push_back(left);
    }

    return tiles;
}

std::vector<sf::Vector2i> getLineArea(sf::Vector2i tile, int min, int max, const Battlefield* bf)
{
    std::vector<sf::Vector2i> tiles;
    sf::Vector2i s(bf->getGridSize());

    bool vertical(std::abs())
}

std::vector<sf::Vector2i> getLinePerpArea(sf::Vector2i tile, int min, int max, const Battlefield* bf)
{

}

}
