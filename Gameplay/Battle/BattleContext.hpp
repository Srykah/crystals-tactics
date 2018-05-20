#ifndef BATTLECONTEXT_HPP_INCLUDED
#define BATTLECONTEXT_HPP_INCLUDED

#include <SFML/Graphics/View.hpp>

class Battlefield;
class UnitList;
class Guild;
namespace gr
{
    class Scene;
    class Cursor;
}
class Cutscene;

enum class BattleStep
{
    Objectives,
    Spawn,
    Combat,
    End
};

struct BattleContext
{
    BattleContext()
    : step(nullptr)
    , advGuild(nullptr)
    , bf(nullptr)
    , ul(nullptr)
    , scene(nullptr)
    , cutscene(nullptr)
    , view(nullptr)
    , cursor(nullptr) {}

    BattleContext(BattleStep&       step,
                  Guild&            advGuild,
                  Battlefield&      bf,
                  UnitList&         ul,
                  gr::Scene&  scene,
                  Cutscene&         cutscene,
                  sf::View&         view,
                  gr::Cursor& cursor)
    : step(&step)
    , advGuild(&advGuild)
    , bf(&bf)
    , ul(&ul)
    , scene(&scene)
    , cutscene(&cutscene)
    , view(&view)
    , cursor(&cursor) {}



    BattleStep*         step;
    Guild*              advGuild;
    Battlefield*        bf;
    UnitList*           ul;
    gr::Scene*    scene;
    Cutscene*           cutscene;
    sf::View*           view;
    gr::Cursor*   cursor;
};


#endif // BATTLECONTEXT_HPP_INCLUDED
