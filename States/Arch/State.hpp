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

Une classe de base représentant un écran de jeu. Chaque écran va hériter de
cette classe et se spécifier à une tâche.
Ainsi, cette classe contient tous les éléments nécessaires à un écran pour
fonctionner correctement :
- Un contexte d'application, dont la fenêtre, les ressources, le lecteur audio,
les données de la partie en cours, etc.
- 3 fonctions pour gérer les évènements, se mettre à jour et se dessiner, qui
sont virtuelles pures pour que les classes filles les spécialisent.
- Un système d'appel à la pile d'écrans de l'application, qui permet à un écran
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

    Constructeur : il ne demande qu'une référence sur la pile d'écrans
    de l'application et son contexte.

    //*/
                        State(StateStack* stack, Context context);
    virtual				~State();

    /*//

    Fonctions de gestion de l'écran : ces fonctions sont appelées
    à tour de rôle pendant la boucle principale du programme.

    Elles sont toutes trois virtuelles pures, car chaque écran
    a une tâche différente à remplir.

    //*/

    virtual void		draw() = 0;
    virtual bool		update(sf::Time dt) = 0;
    virtual bool		handleEvent(const Input::Event& event) = 0;
    virtual bool        handleSignal(const Signal& signal) = 0;

protected:
    void                emit(Signal::Data& data); //Fonction d'émission de signal

    StateStack*			mStack;
    Context				mContext;
};

}

#endif // STATE_HPP_INCLUDED
