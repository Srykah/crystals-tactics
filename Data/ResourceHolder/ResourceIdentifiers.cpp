#include "Data/ResourceHolder/ResourceIdentifiers.hpp"

Entities::ID CharTypeToEntitiesID(CharType type)
{
    #define TYPETOENTITY_CASE(JOB) case CharType::JOB: return Entities::JOB;

    switch(type)
    {
    TYPETOENTITY_CASE(Protector)
    /*
    TYPETOENTITY_CASE(Mechanics)
    TYPETOENTITY_CASE(Medic)
    TYPETOENTITY_CASE(Spy)
    TYPETOENTITY_CASE(Murderer)
    TYPETOENTITY_CASE(Android)
    TYPETOENTITY_CASE(DogRobot)
    */

    default:
        return Entities::Unknown;
    }
}
