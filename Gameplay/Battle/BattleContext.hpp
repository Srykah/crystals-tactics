#ifndef BATTLECONTEXT_HPP_INCLUDED
#define BATTLECONTEXT_HPP_INCLUDED

class Battlefield;
class UnitList;
class Guild;
namespace Graphism { class Scene; }
class Cutscene;

struct BattleContext
{
    BattleContext() : advGuild(nullptr), bf(nullptr), ul(nullptr), scene(nullptr), cutscene(nullptr) {}
    BattleContext(Guild& advGuild, Battlefield& bf, UnitList& ul, Graphism::Scene& scene, Cutscene& cutscene) :
        advGuild(&advGuild), bf(&bf), ul(&ul), scene(&scene), cutscene(&cutscene) {}

    Guild* advGuild;
    Battlefield* bf;
    UnitList* ul;
    Graphism::Scene* scene;
    Cutscene* cutscene;
};


#endif // BATTLECONTEXT_HPP_INCLUDED
