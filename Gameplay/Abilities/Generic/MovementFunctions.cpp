#include "Gameplay/Abilities/Generic/Movement.hpp"
#include "Gameplay/Battle/Battlefield.hpp"
#include "Gameplay/Battle/UnitList.hpp"
#include "Gameplay/Character/Character.hpp"

void Movement::getMovementTiles(MovementTiles& tilesList, int x, int y, short mobility) const
{
    BattleContext bc(user->getBattleContext());
    sf::Vector2i from(x,y);
    Character* unit(bc.ul->getUnitByTile(from));

    if (mobility >= 0                                               //si il reste de la distance à parcourir,
        && (bc.bf->contains(from))                                  //que la case est bien dans le cadre,
        && !(bc.bf->isWall(from))                                   //que ce n'est ni un mur,
        && (unit == nullptr || unit->isAlly() == user->isAlly())    //ni un ennemi,
        && (!tilesList.count(y) || !tilesList.at(y).count(x) || tilesList[y][x] < mobility)
            // enfin si la case n'est pas dans la liste, ou si celle déjà présente est moins bien,
    {
        tilesList[y][x] = mobility; //on met à jour la liste,
        //puis on regarde si les cases autour peuvent être ajoutées aussi, en décrémentant la mobilité
        getMovementTiles(tilesList, x, y-1, mobility-1); //en haut
        getMovementTiles(tilesList, x+1, y, mobility-1); //à gauche
        getMovementTiles(tilesList, x-1, y, mobility-1); //à droite
        getMovementTiles(tilesList, x, y+1, mobility-1); //en bas
    }

    /* À la fin de la récursivité, la liste envoyée en paramètre contiendra
    toutes les tuiles et la mobilité restante maximale depuis la case de départ.
    Pour reconstruire le chemin voulu il suffira de suivre l'ordre croissant
    à partir de la case visée. */
}

void Movement::fillCutscene(const Path& path, Character* user)
{

}

}
