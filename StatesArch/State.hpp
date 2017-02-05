#ifndef BOOK_STATE_HPP
#define BOOK_STATE_HPP

#include "../States/StateIdentifiers.hpp"
#include "../Other/ResourceIdentifiers.hpp"
#include "../Other/ResourceHolder.hpp"
#include "../Data/GameDataIdentifiers.hpp"
#include "../Input/InputHandler.hpp"
#include "../StatesArch/StateData.hpp"
#include "../StatesArch/StateRequerer.hpp"
#include "../Data/JobsData.hpp"
#include "../Data/AbilityData.hpp"
#include "../Data/ItemsData.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

namespace sf
{
	class RenderWindow;
	class RenderTexture;
}

class StateStack;
class MusicPlayer;
class SoundPlayer;
class Guild;
class MissionList;
class Character;

/*//

State

Une classe de base repr�sentant un �cran de jeu. Chaque �cran va h�riter de
cette classe et se sp�cifier � une t�che.
Ainsi, cette classe contient tous les �l�ments n�cessaires � un �cran pour
fonctionner correctement :
- Un contexte d'application, dont la fen�tre, les ressources, le lecteur audio,
les donn�es de la partie en cours, etc.
- 3 fonctions pour g�rer les �v�nements, se mettre � jour et se dessiner, qui
sont virtuelles pures pour que les classes filles les sp�cialisent.
- Un syst�me d'appel � la pile d'�crans de l'application, qui permet � un �cran
d'en lancer un autre, ou de se fermer tout seul, par exemple.
-

//*/

class State
{
public:
    typedef std::unique_ptr<State> Ptr;

    /*//

    Context

    Cette structure g�re le contexte d'application dans lequel l'�cran est
    ouvert.
    Il contient, dans l'ordre :
    - la fen�tre, pour avoir sa taille ou la position de la souris ;
    - la texture de rendu, pour dessiner l'�cran dedans ;
    - les textures g�n�riques � l'appli dont pourrait se servir l'�cran ;
    - les polices d'�criture de l'appli ;
    - le lecteur de musique ;
    - le lecteur de sons ;
    - les entit�s g�n�riques � l'appli ;
    - la guilde de la partie en cours ;
    - la liste de missions de la partie en cours.

    //*/

    struct Context
    {
        Context(sf::RenderWindow& window,
                IH& inputHandler,
                TextureHolder& textures,
                FontHolder& fonts,
                MusicPlayer& music,
                SoundPlayer& sounds,
                EntityHolder& entities,
                Data::StatsData& stats, Data::ItemsData& items, Data::AbsData& abilities,
                Guild& guild);

        sf::RenderWindow*	window;
        IH*                 inputHandler;
        TextureHolder*		textures;
        FontHolder*			fonts;
        MusicPlayer*		music;
        SoundPlayer*		sounds;
        EntityHolder*       entities;
        Data::StatsData*    stats;
        Data::ItemsData*    items;
        Data::AbsData*      abilities;
        Guild*              guild;

    };

public:

    /*//

    Constructeur : il ne demande qu'une r�f�rence sur la pile d'�crans
    de l'application et son contexte.

    //*/
                        State(StateStack& stack, Context context);
    virtual				~State();

    virtual States::ID  getID() const = 0;

    /*//

    Fonctions de gestion de l'�cran : ces fonctions sont appel�es
    � tour de r�le pendant la boucle principale du programme.

    Elles sont toutes trois virtuelles pures, car chaque �cran
    a une t�che diff�rente � remplir.

    //*/

    virtual void		draw() = 0;
    virtual bool		update(sf::Time dt) = 0;
    virtual bool		handleInput(const sf::Event& event, IH::SA stdAc, sf::Vector2f mousePos) = 0;

    Context				getContext() const;

protected:

    /*//

    Fonctions de manipulation de la pile d'�crans

    //*/

    void				requestStackPush(States::ID stateID, const StateData& = StateData(), bool front = false);
    void				requestStackPop(bool front = false);
    void                requestStackClose(bool front = false);
    void                requestStackCloseTop(bool front = false);
    void                requestStackCloseType(States::ID stateID, bool front = false);
    void                requestStackCloseOthers(bool front = false);
    void				requestStackClear(bool front = false);
    void                requestStackAction(StateRequest req, bool front = false);

    void                setData(const StateData& sd);
    const StateData&    getData(States::ID stateID) const;

private:
    StateStack*			mStack;
    Context				mContext;
};

#endif // BOOK_STATE_HPP
