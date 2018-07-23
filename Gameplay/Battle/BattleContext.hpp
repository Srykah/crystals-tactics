#ifndef BATTLECONTEXT_HPP_INCLUDED
#define BATTLECONTEXT_HPP_INCLUDED

namespace sf { class View; }
class Battlefield;
class UnitList;
class Guild;
namespace gr
{
    class Scene;
    class Cursor;
}
class Cutscene;

namespace bt
{

struct BattleContext
{
    BattleContext(Guild&        oppGuild,
                  Battlefield&  bf,
                  UnitList&     ul,
                  gr::Scene&    scene,
                  Cutscene&     cutscene,
                  gr::Cursor&   cursor,
                  sf::View&     view)
    : oppGuild(oppGuild)
    , bf(bf)
    , ul(ul)
    , scene(scene)
    , cutscene(cutscene)
    , cursor(cursor)
    , view(view) {}



    Guild&              oppGuild;
    Battlefield&        bf;
    UnitList&           ul;
    gr::Scene&          scene;
    Cutscene&           cutscene;
    gr::Cursor&         cursor;
    sf::View&           view;
};

}

#endif // BATTLECONTEXT_HPP_INCLUDED
