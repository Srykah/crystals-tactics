#include "Gameplay/Abilities/AbilityFunctions.hpp"
#include "Gameplay/Character/Character.hpp"
#include "Gameplay/Battle/UnitList.hpp"
#include "Gameplay/Battle/Battlefield.hpp"
#include "Gameplay/Items/Weapon.hpp"
#include "Other/Utility.hpp"
#include <iostream>

namespace Ab
{

bool isVisible(const Character* user, sf::Vector2i cible)
{
    BattleContext bc(user->getBattleContext());

	if (!bc.bf->contains(cible)) // check if cible is in the battlefield
        return false;

	sf::Vector2i origine(user->getCoords());

	// we only check in the rectangle around the line of sight
	int min_x = std::min(origine.x, cible.x);
	int max_x = std::max(origine.x, cible.x);
	int min_y = std::min(origine.y, cible.y);
	int max_y = std::max(origine.y, cible.y);
	int x_center(2*origine.x+1), y_center(2*origine.y+1);

	// we create a vector normal to the line of sight, so that dot product gives relative position
	sf::Vector2i normal(cible.y-origine.y, origine.x-cible.x);

	for (int y(min_y); y <= max_y; y++)
	{
		for (int x(min_x); x <= max_x; x++)
		{
			/* get the positions of the corners of the tile relative to the line of sight
			   (1 = corner is on the left of the line, -1 = right, 0 = corner is on the line) */
			int upLeft(signe(scal(2*x, 2*y, x_center, y_center)));
			int upRight(signe(scal(2*x+2, 2*y, x_center, y_center)));
			int downLeft(signe(scal(2*x, 2*y+2, x_center, y_center)));
			int downRight(signe(scal(2*x+2, 2*y+2, x_center, y_center)));
            /* the rectangle intersects the line of sight iff the absolute value
               of the sum of the relative positions of the corners is <= 2 */

            sf::Vector2i tile(x,y);
			if (tile != origine && tile != cible                        // we ignore the beginning and end tiles.
                && std::abs(upLeft+upRight+downLeft+downRight) <= 2     // if this tile intersects with the line of sight,
                && (bc.bf->getProps(tile).blocking                      // and it is blocking
                    || bc.ul->getUnitByTile(tile) != nullptr))          // or there's a character on it,
				return false;                                           // the target is not reachable.
		}
	}

	return true;
}

/*
bool isVisible(const Character* user, sf::Vector2i tile) // to rewrite
{
    if (!sf::IntRect(sf::Vector2i(0,0), user->getBattleContext().bf->getGridSize()).contains(tile))
        return false;

    sf::Vector2f c(user->getCoords());
    sf::Vector2f line(sf::Vector2f(tile)-c);
    c += sf::Vector2f(0.5, 0.5);
    sf::Vector2f u(unitVector(line));

    for (float t(0.8); t < length(line); t += 0.3)
    {
        sf::Vector2i currentTile(c+t*u);

        if (user->getBattleContext().bf->isWall(currentTile)
            || (currentTile != tile and user->getBattleContext().ul->getUnitByTile(currentTile) != nullptr))
            return false;
    }

    return true;
}
*/

std::vector<sf::Vector2i> circleRange(const Character* user, int min, int max)
{
    std::vector<sf::Vector2i> tiles;
    sf::Vector2i c(user->getCoords());

    // si la portée min est 0, on inclut la case du lanceur
    if (min == 0)
        tiles.push_back(c);
    // on parcourt la grille par carrés concentriques de rayon croissant
    for (int rayon(min >= 1 ? min : 1); rayon <= max; rayon++)
    {
        for (int diagonale = 0; diagonale < rayon; diagonale++)
        {
            // on parcourt chaque carré selon ses 4 diagonales (sens horaire, origine en haut)

            // diagonale sens bas-droit (du nord à l'est)
            sf::Vector2i ne(c.x+diagonale, c.y-rayon+diagonale);
            if (isVisible(user, ne))
                tiles.push_back(ne);

            // diagonale sens bas-gauche (de l'est au sud)
            sf::Vector2i se(c.x+rayon-diagonale, c.y+diagonale);
            if (isVisible(user, se))
                tiles.push_back(se);

            // diagonale sens haut-gauche (du sud à l'ouest)
            sf::Vector2i sw(c.x-diagonale, c.y+rayon-diagonale);
            if (isVisible(user, sw))
                tiles.push_back(sw);

            // diagonale sens haut-droit (de l'ouest au nord)
            sf::Vector2i nw(c.x-rayon+diagonale, c.y-diagonale);
            if (isVisible(user, nw))
                tiles.push_back(nw);
        }
    }

    return tiles;
}

std::vector<sf::Vector2i> squareRange(const Character* user, int min, int max)
{
    std::vector<sf::Vector2i> tiles;
    sf::Vector2i c(user->getCoords());

    // si la portée min est 0, on inclut la case du lanceur
    if (min == 0)
        tiles.push_back(c);
    // on parcourt la grille par carrés concentriques de rayon croissant
    for (int rayon(min >= 1 ? min : 1); rayon <= max; rayon++)
    {
        for (int cote = 0; cote < 2*rayon; cote++)
        {
            // on parcourt chaque carré selon ses 4 côtés (sens horaire, origine en haut à droite)

            // côté haut (vers la gauche)
            sf::Vector2i up(c.x-rayon+cote, c.y-rayon);
            if (isVisible(user, up))
                tiles.push_back(up);

            // côté droit (vers le bas)
            sf::Vector2i right(c.x+rayon, c.y-rayon+cote);
            if (isVisible(user, right))
                tiles.push_back(right);

            // côté bas (vers la droite)
            sf::Vector2i down(c.x+rayon-cote, c.y+rayon);
            if (isVisible(user, down))
                tiles.push_back(down);

            // côté gauche (vers le haut)
            sf::Vector2i left(c.x-rayon, c.y+rayon-cote);
            if (isVisible(user, left))
                tiles.push_back(left);
        }
    }

    return tiles;
}

std::vector<sf::Vector2i> crossRange(const Character* user, int min, int max)
{
    std::vector<sf::Vector2i> tiles;
    sf::Vector2i c(user->getCoords());

    // si la portée min est 0, on inclut la case du lanceur
    if (min == 0)
        tiles.push_back(c);
    // on parcourt la grille par lignes pour chaque direction
    for (int decal(min >= 1 ? min : 1); decal <= max; decal++)
    {
        // côté haut
        sf::Vector2i up(c.x, c.y-decal);
        if (isVisible(user, up))
            tiles.push_back(up);

        // côté droit
        sf::Vector2i right(c.x+decal, c.y);
        if (isVisible(user, right))
            tiles.push_back(right);

        // côté bas
        sf::Vector2i down(c.x, c.y+decal);
        if (isVisible(user, down))
            tiles.push_back(down);

        // côté gauche
        sf::Vector2i left(c.x-decal, c.y);
        if (isVisible(user, left))
            tiles.push_back(left);
    }

    return tiles;
}

std::vector<sf::Vector2i> circleArea(sf::Vector2i tile, int min, int max, const Battlefield* bf)
{
    std::vector<sf::Vector2i> tiles;

    // si la portée min est 0, on inclut la case visée
    if (min == 0)
        tiles.push_back(tile);
    // on parcourt la grille par carrés concentriques de rayon croissant
    for (int rayon(min >= 1 ? min : 1); rayon <= max; rayon++)
    {
        for (int diagonale = 0; diagonale < rayon; diagonale++)
        {
            // on parcourt chaque carré (incliné à 45°) selon ses 4 côtés (sens horaire, début en haut)

            // du nord à l'est
            sf::Vector2i ne(tile.x+diagonale, tile.y-rayon+diagonale);
            if (bf->contains(ne) && !bf->getProps(ne).blocking)
                tiles.push_back(ne);

            // de l'est au sud
            sf::Vector2i es(tile.x+rayon-diagonale, tile.y+diagonale);
            if (bf->contains(es) && !bf->getProps(es).blocking)
                tiles.push_back(es);

            // du sud à l'ouest
            sf::Vector2i sw(tile.x-diagonale, tile.y+rayon-diagonale);
            if (bf->contains(sw) && !bf->getProps(sw).blocking)
                tiles.push_back(sw);

            // de l'ouest au nord
            sf::Vector2i wn(tile.x-rayon+diagonale, tile.y-diagonale);
            if (bf->contains(wn) && !bf->getProps(wn).blocking)
                tiles.push_back(wn);
        }
    }

    return tiles;
}

std::vector<sf::Vector2i> squareArea(sf::Vector2i tile, int min, int max, const Battlefield* bf)
{
    std::vector<sf::Vector2i> tiles;
    sf::Vector2i s(bf->getGridSize());

    // si la portée min est 0, on inclut la case du lanceur
    if (min == 0)
        tiles.push_back(tile);
    // on parcourt la grille par carrés concentriques de rayon croissant
    for (int rayon(min >= 1 ? min : 1); rayon <= max; rayon++)
    {
        for (int cote = 0; cote < 2*rayon; cote++)
        {
            // on parcourt chaque carré selon ses 4 côtés (sens horaire, début en haut à droite)

            // côté haut (vers la gauche)
            sf::Vector2i up(tile.x-rayon+cote, tile.y-rayon);
            if (bf->contains(up) && !bf->getProps(up).blocking)
                tiles.push_back(up);

            // côté droit (vers le bas)
            sf::Vector2i right(tile.x+rayon, tile.y-rayon+cote);
            if (bf->contains(right) && !bf->getProps(right).blocking)
                tiles.push_back(right);

            // côté bas (vers la droite)
            sf::Vector2i down(tile.x+rayon-cote, tile.y+rayon);
            if (bf->contains(down) && !bf->getProps(down).blocking)
                tiles.push_back(down);

            // côté gauche (vers le haut)
            sf::Vector2i left(tile.x-rayon, tile.y+rayon-cote);
            if (bf->contains(left) && !bf->getProps(left).blocking)
                tiles.push_back(left);
        }
    }

    return tiles;
}

std::vector<sf::Vector2i> crossArea(sf::Vector2i tile, int min, int max, const Battlefield* bf)
{
    std::vector<sf::Vector2i> tiles;

    // si la portée min est 0, on inclut la case du lanceur
    if (min == 0)
        tiles.push_back(tile);
    // on parcourt la grille par lignes pour chaque direction
    for (int decal = (min >= 1 ? min : 1); decal <= max; decal++)
    {
        // haut
        sf::Vector2i up(tile.x, tile.y-decal);
        if (bf->contains(up) && !bf->getProps(up).blocking)
            tiles.push_back(up);

        // droite
        sf::Vector2i right(tile.x+decal, tile.y);
        if (bf->contains(right) && !bf->getProps(right).blocking)
            tiles.push_back(right);

        // bas
        sf::Vector2i down(tile.x, tile.y+decal);
        if (bf->contains(down) && !bf->getProps(down).blocking)
            tiles.push_back(down);

        // gauche
        sf::Vector2i left(tile.x, tile.y-decal);
        if (bf->contains(left) && !bf->getProps(left).blocking)
            tiles.push_back(left);
    }

    return tiles;
}

std::vector<sf::Vector2i> lineArea(sf::Vector2i tile, int min, int max, const Battlefield* bf, sf::Vector2i userCoords)
{
    std::vector<sf::Vector2i> tiles;
    Direction::Dir dir(dirTowards(userCoords, tile));

    if (min == 0)
        tiles.push_back(tile);

    switch(dir)
    {
    case Direction::Down:
        for (int i(min); i <= max; i++)
        {
            sf::Vector2i cur(tile.x, tile.y+i);
            if (bf->contains(cur) && !bf->getProps(cur).blocking)
                tiles.push_back(cur);
        }
        break;
    case Direction::Right:
        for (int i(min); i <= max; i++)
        {
            sf::Vector2i cur(tile.x+i, tile.y);
            if (bf->contains(cur) && !bf->getProps(cur).blocking)
                tiles.push_back(cur);
        }
        break;
    case Direction::Up:
        for (int i(min); i <= max; i++)
        {
            sf::Vector2i cur(tile.x, tile.y-i);
            if (bf->contains(cur) && !bf->getProps(cur).blocking)
                tiles.push_back(cur);
        }
        break;
    case Direction::Left:
        for (int i(min); i <= max; i++)
        {
            sf::Vector2i cur(tile.x-i, tile.y);
            if (bf->contains(cur) && !bf->getProps(cur).blocking)
                tiles.push_back(cur);
        }
    default:;
    }

    return tiles;
}

std::vector<sf::Vector2i> linePerpArea(sf::Vector2i tile, int min, int max, const Battlefield* bf, sf::Vector2i userCoords)
{
    std::vector<sf::Vector2i> tiles;
    Direction::Dir dir(dirTowards(userCoords, tile));

    switch(dir)
    {
    case Direction::Down:
    case Direction::Up:
        for (int i(min >= 1 ? min : 1); i <= max; i++)
        {
            sf::Vector2i left(tile.x-1, tile.y);
            if (bf->contains(left) && !bf->getProps(left).blocking)
                tiles.push_back(left);

            sf::Vector2i right(tile.x+1, tile.y);
            if (bf->contains(right) && !bf->getProps(right).blocking)
                tiles.push_back(right);
        }
        break;
    case Direction::Right:
    case Direction::Left:
        for (int i(min >= 1 ? min : 1); i <= max; i++)
        {
            sf::Vector2i up(tile.x, tile.y-1);
            if (bf->contains(up) && !bf->getProps(up).blocking)
                tiles.push_back(up);

            sf::Vector2i down(tile.x, tile.y+1);
            if (bf->contains(down) && !bf->getProps(down).blocking)
                tiles.push_back(down);
        }
    default:;
    }

    return tiles;
}

Direction::Dir dirTowards(sf::Vector2i from, sf::Vector2i to)
{
    if (std::abs(from.x-to.x) <= std::abs(from.y-to.y)) // si la case visée est à la verticale (large) du lanceur
    {
        if (from.y > to.y)
            return Direction::Up; // si elle est au-dessus (strictement), on renvoie haut.
        else if (from.y < to.y)
            return Direction::Down; // si elle est en-dessous (strictement), on renvoie bas.
        else
            return Direction::None; // Dans le dernier cas, les deux cases sont identiques, on renvoie None.
    }
    else
    {
        if (from.x > to.x) // si elle est à gauche (strictement)
            return Direction::Left;
        // si elle est à droite (ici, c'est forcément strictement car le cas d'égalité a déjà été traité)
        return Direction::Right;
    }
}

Direction::Angle getAngle(sf::Vector2i from, Character* target)
{
    // note : par défaut on renvoie Front si c'est la même case

    Direction::Dir facing(target->getFacing());
    sf::Vector2i offset(from-target->getCoords());

    if ((offset.x >=  std::abs(offset.y) && facing == Direction::Right)
     || (offset.x <= -std::abs(offset.y) && facing == Direction::Left)
     || (offset.y >=  std::abs(offset.x) && facing == Direction::Down)
     || (offset.y <= -std::abs(offset.x) && facing == Direction::Up))
    {
        return Direction::Front;
    }
    else if ((offset.x >  std::abs(offset.y) && facing == Direction::Left)
          || (offset.x < -std::abs(offset.y) && facing == Direction::Right)
          || (offset.y >  std::abs(offset.x) && facing == Direction::Up)
          || (offset.y < -std::abs(offset.x) && facing == Direction::Down))
    {
        return Direction::Back;
    }
    else
        return Direction::Side;
}

bool escapes(const Character* charac, Direction::Angle angle)
{
    if (angle == Direction::Front)
        return (randomFloatNorm() * 100.f < charac->getStats().evasion);
    else if (angle == Direction::Side)
        return (randomFloatNorm() * 200.f < charac->getStats().evasion);
    else // if (angle == Direction::Back)
        return (randomFloatNorm() * 500.f < charac->getStats().evasion);
}

bool counterattacks(const Character* charac, Direction::Angle angle)
{
    if (angle == Direction::Front)
        return true;
    else if (angle == Direction::Side)
        return (randomFloatNorm() < 0.5f);
    else // if (angle == Direction::Back)
        return (randomFloatNorm() < 0.2f);
}

void dealDamage(Stat baseDmg, Character* attacker, Character* target, Element elem, StatusAilment ailment)
{
    Direction::Angle angle(getAngle(attacker->getCoords(), target));

    if(escapes(target, angle)) //if the target escapes from this angle
    {
        std::cout << target->getName() << "evaded !" << std::endl;
        target->getEntity()->setAnimation("evade");
    }
    else
    {
        Stat atk = attacker->getStats().attack, def = target->getStats().defense;
        Stat damage(baseDmg + randomPick(atk) - 0.5*randomPick(def));

        if(randomFloatNorm() * (angle == Direction::Back ? 50.f : 100.f) < attacker->getStats().critHitRate) //on critical hit
        {
            std::cout << "CRITICAL HIT ! ";
            damage *= 2;
            pushFrom(target, attacker->getCoords());
        }
        if(elem != Element::None)
            damage = Stat(damage * target->getAffinities().aff.at(elem));

        target->receiveDamage(damage);

        std::cout << target->getName() << " receives " << damage << " damage !" << std::endl;
    }
}

void pushFrom(Character* charac, sf::Vector2i from, int tile_count)
{

}

}
