#ifndef STATE_HPP_INCLUDED
#define STATE_HPP_INCLUDED

#include "States/Arch/Context.hpp"
#include "States/Arch/Signal.hpp"
#include "Input/Listener.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

namespace sf
{
	class RenderWindow;
	class RenderTexture;
}

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

namespace States
{

class StateStack;

class State
{
public:
    typedef std::unique_ptr<State> Ptr;

public:

    /*//

    Constructeur : il ne demande qu'une r�f�rence sur la pile d'�crans
    de l'application et son contexte.

    //*/
                        State(StateStack* stack, Context context);
    virtual				~State();

    /*//

    Fonctions de gestion de l'�cran : ces fonctions sont appel�es
    � tour de r�le pendant la boucle principale du programme.

    Elles sont toutes trois virtuelles pures, car chaque �cran
    a une t�che diff�rente � remplir.

    //*/

    virtual void		draw() = 0;
    virtual bool		update(sf::Time dt) = 0;
    virtual bool		handleEvent(const Input::Event& event) = 0;
    virtual bool        handleSignal(const Signal& signal) = 0;

protected:
    void                emit(Signal::Data& data); //Fonction d'�mission de signal

    StateStack*			mStack;
    Context				mContext;
};

}

#endif // STATE_HPP_INCLUDED
