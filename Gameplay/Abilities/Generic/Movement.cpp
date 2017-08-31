#include "Gameplay/Abilities/Generic/Movement.hpp"
#include "Gameplay/Abilities/AbilityFunctions.hpp"
#include "Gameplay/Character/Character.hpp"
#include "Gameplay/Battle/Battlefield.hpp"
#include "Gameplay/Battle/UnitList.hpp"

namespace
{

using Path = std::deque<Direction::Dir>;
using MovementTiles = std::map< int, std::map< int, int > >;

void getMovementTiles(MovementTiles& tilesList, int x, int y, short mobility, BattleContext bc, bool ally)
{
    sf::Vector2i from(x,y);
    Character* unit(bc.ul->getUnitByTile(from));

    if (mobility >= 0                                   // si il reste de la distance � parcourir,
        && bc.bf->contains(from)                        // que la case est bien dans le cadre,
        && bc.bf->getProps(from).walkable               // qu'on peut marcher dessus,
        && (unit == nullptr || unit->isAlly() == ally)  // qu'elle ne contient pas un ennemi,
        && (!tilesList.count(y) || !tilesList.at(y).count(x) || tilesList[y][x] < mobility))
            // enfin si la case n'est pas dans la liste, ou si celle d�j� pr�sente est moins bien,
    {
        tilesList[y][x] = mobility; //on met � jour la liste,
        //puis on regarde si les cases autour peuvent �tre ajout�es aussi, en d�cr�mentant la mobilit�
        getMovementTiles(tilesList, x, y-1, mobility-1, bc, ally); //en haut
        getMovementTiles(tilesList, x+1, y, mobility-1, bc, ally); //� gauche
        getMovementTiles(tilesList, x-1, y, mobility-1, bc, ally); //� droite
        getMovementTiles(tilesList, x, y+1, mobility-1, bc, ally); //en bas
    }

    /* � la fin de la r�cursivit�, la liste envoy�e en param�tre contiendra
    toutes les tuiles et la mobilit� restante maximale depuis la case de d�part.
    Pour reconstruire le chemin voulu il suffira de suivre l'ordre croissant
    � partir de la case vis�e. */
}

void createPath(Path& path, const MovementTiles& tilesList, int x, int y, short mob)
{
    if (tilesList.count(y-1) && tilesList.at(y-1).count(x) && tilesList.at(y-1).at(x) > mob) //up tile
    {
        path.push_front(Direction::Down);
        createPath(path, tilesList, x, y-1, tilesList.at(y-1).at(x));
    }
    else if (tilesList.count(y+1) && tilesList.at(y+1).count(x) && tilesList.at(y+1).at(x) > mob) //down tile
    {
        path.push_front(Direction::Up);
        createPath(path, tilesList, x, y+1, tilesList.at(y+1).at(x));
    }
    else if (tilesList.count(y) && tilesList.at(y).count(x-1) && tilesList.at(y).at(x-1) > mob) //left tile
    {
        path.push_front(Direction::Right);
        createPath(path, tilesList, x-1, y, tilesList.at(y).at(x-1));
    }
    else if (tilesList.count(y) && tilesList.at(y).count(x+1) && tilesList.at(y).at(x+1) > mob) //right tile
    {
        path.push_front(Direction::Left);
        createPath(path, tilesList, x+1, y, tilesList.at(y).at(x+1));
    }
}

}

namespace Ab {

Movement::Movement()
: Ability("D�placement", "Permet de se d�placer sur la carte, d'autant de cases que la mobilit� (ou moins).", 1)
{

}

Movement::~Movement()
{

}

std::vector<sf::Vector2i> Movement::getRange(Character* user) const
{
    BattleContext bc(user->getBattleContext());

    MovementTiles tilesList;
    sf::Vector2i c(user->getCoords());
    getMovementTiles(tilesList, c.x, c.y, user->getStats().mobility, bc, user->isAlly());

    std::vector<sf::Vector2i> tiles;
    for (auto row : tilesList)
    {
        for (auto col : row.second)
        {
            sf::Vector2i tile(col.first, row.first);
            if (bc.ul->getUnitByTile(tile) == nullptr)
                tiles.push_back(tile);
        }
    }

    return tiles;
}

std::vector<sf::Vector2i> Movement::getArea(Character* user, sf::Vector2i to) const
{
    return std::vector<sf::Vector2i>(1, to);
}

void Movement::use(Character* user, sf::Vector2i to) const
{
    BattleContext bc(user->getBattleContext());

    sf::Vector2i c(user->getCoords());
    MovementTiles tiles;
    getMovementTiles(tiles, c.x, c.y, user->getStats().mobility, bc, user->isAlly());
    Path path;
    createPath(path, tiles, to.x, to.y, 0);

    user->getEntity()->setAnimation("walking");

    for (Direction::Dir dir : path)
    {
        sf::Vector2i dirVec((dir == Direction::Right) - (dir == Direction::Left),
                            (dir == Direction::Down) - (dir == Direction::Up));

        bc.cutscene->addEvent(CutsceneEvent([user, dir, dirVec]()
        {
            user->getEntity()->setFacing(dir);
            user->getNode()->setEffect(Graphism::Effect(sf::milliseconds(250.f), float(TILE_DIM)*sf::Vector2f(dirVec), dirVec.y));
        },
        [user](sf::Time delta){ return user->getNode()->isEffectFinished(); },
        [user, dirVec]()
        {
            user->moveCoords(dirVec);
        }));
    }

    bc.cutscene->addEvent(CutsceneEvent([user](){ user->getEntity()->setAnimation("idle"); }));
}

}
