#include "Gameplay/Character/Identity.hpp"

namespace
{

const char sexToString[][] = {
    "male",
    "female",
    "none"
};

const std::unordered_map< std::string, Sex> stringToSex({
    {"male", Male},
    {"female", Female},
    {"none", None}
});

const char raceToString[][] = {
    "bio",
    "mech",
    "hybrid",
    "other"
};

const std::unordered_map< std::string, Sex> stringToRace({
    {"bio", Bio},
    {"mech", Mech},
    {"hybrid", Hybrid},
    {"other", Other}
});

const char jobToString[][] = { "bio", "mech", "hybrid", "other"};

const std::unordered_map< std::string, Sex> stringToRace({ {"bio", Bio}, {"mech", Mech}, {"hybrid", Hybrid}, {"other", Other} });

}

void ch::Identity::load(pugi::xml_node node)
{
    ID = node.attribute("id").as_int();
    name = node.attribute("name").as_string();
    sex = toSex()
    job =
    mRole = StrToCharRole(node.attribute("role").as_string());
    mAIType = StrToAI(node.attribute("ai").as_string());
}
