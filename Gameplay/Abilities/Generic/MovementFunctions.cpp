#include "Gameplay/Abilities/Generic/Movement.hpp"
#include "Gameplay/Battle/Battlefield.hpp"
#include "Gameplay/Battle/UnitList.hpp"
#include "Gameplay/Character/Character.hpp"

void Movement::getMovementTiles(MovementTiles& tilesList, int x, int y, short mobility) const
{
    BattleContext bc(user->getBattleContext());
    sf::Vector2i from(x,y);
    Character* unit(bc.ul->getUnitByTile(from));

    if (mobility >= 0                                               //si il reste de la distance � parcourir,
        && (bc.bf->contains(from))                                  //que la case est bien dans le cadre,
        && !(bc.bf->isWall(from))                                   //que ce n'est ni un mur,
        && (unit == nullptr || unit->isAlly() == user->isAlly())    //ni un ennemi,
        && (!tilesList.count(y) || !tilesList.at(y).count(x) || tilesList[y][x] < mobility)
            // enfin si la case n'est pas dans la liste, ou si celle d�j� pr�sente est moins bien,
    {
        tilesList[y][x] = mobility; //on met � jour la liste,
        //puis on regarde si les cases autour peuvent �tre ajout�es aussi, en d�cr�mentant la mobilit�
        getMovementTiles(tilesList, x, y-1, mobility-1); //en haut
        getMovementTiles(tilesList, x+1, y, mobility-1); //� gauche
        getMovementTiles(tilesList, x-1, y, mobility-1); //� droite
        getMovementTiles(tilesList, x, y+1, mobility-1); //en bas
    }

    /* � la fin de la r�cursivit�, la liste envoy�e en param�tre contiendra
    toutes les tuiles et la mobilit� restante maximale depuis la case de d�part.
    Pour reconstruire le chemin voulu il suffira de suivre l'ordre croissant
    � partir de la case vis�e. */
}

void Movement::fillCutscene(const Path& path, Character* user)
{

}

}
