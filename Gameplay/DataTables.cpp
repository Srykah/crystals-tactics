#include "DataTables.hpp"
#include "../Data/GameDataIdentifiers.hpp"

std::vector<MissionData> initializeMissionData()
{
    std::vector<MissionData> data;
    data.resize(Missions::MissionCount);

    data[Missions::Mission00_Prologue].rank = 0;
    data[Missions::Mission00_Prologue].name = "Prologue";
    data[Missions::Mission00_Prologue].description = "C'est ici que la légende commence";
    data[Missions::Mission00_Prologue].prime = 1000;
    data[Missions::Mission00_Prologue].battlePath = "Media/Missions/Mission00_Prologue.CT";

    return data;
}
