#include "../Gameplay/GameplayUtility.hpp"

std::string convertTypeToString(Character::Type type)
{
    #define JOBTOSTRING_CASE(JOB) case Character::JOB: return #JOB;

    switch(type)
    {
    JOBTOSTRING_CASE(Tank)
    JOBTOSTRING_CASE(Mechanics)
    JOBTOSTRING_CASE(Medic)
    JOBTOSTRING_CASE(Gunner)
    JOBTOSTRING_CASE(Murderer)

    default:
        return "Unknown";
    }
}

Character::Type convertStringToType(std::string text)
{
    #define STRINGTOJOB_IF(TEXT, JOB) if (TEXT == #JOB) return Character::JOB;

         STRINGTOJOB_IF(text, Tank)
    else STRINGTOJOB_IF(text, Mechanics)
    else STRINGTOJOB_IF(text, Medic)
    else STRINGTOJOB_IF(text, Gunner)
    else STRINGTOJOB_IF(text, Murderer)
    else return Character::Unknown;
}

Entities::ID convertTypeToEntitiesID(Character::Type type)
{
    #define TYPETOENTITY_CASE(JOB) case Character::JOB: return Entities::JOB;

    switch(type)
    {
    TYPETOENTITY_CASE(Tank)
    TYPETOENTITY_CASE(Mechanics)
    TYPETOENTITY_CASE(Medic)
    TYPETOENTITY_CASE(Gunner)
    TYPETOENTITY_CASE(Murderer)

    default:
        return Entities::Unknown;
    }
}

