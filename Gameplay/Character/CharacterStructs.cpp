#include "CharacterStructs.hpp"

sf::String CharTypeToStr(CharType type)
{
    switch(type)
    {
    case CharType::Protector:   return "Protector";
    case CharType::Medic:       return "Medic";
    case CharType::Sniper:      return "Sniper";
    case CharType::Mechanics:   return "Mechanics";
    case CharType::Spy:         return "Spy";
    case CharType::Physicist:   return "Physicist";
    case CharType::Bomber:      return "Bomber";
    case CharType::Acrobat:     return "Acrobat";
    default:                    return "Unknown";
    }
}

CharType StrToCharType(const sf::String& text)
{
    #define STRINGTOJOB_IF(TEXT, JOB) if (TEXT == #JOB) return CharType::JOB;

         STRINGTOJOB_IF(text, Protector)
    /*
    else STRINGTOJOB_IF(text, Mechanics)
    else STRINGTOJOB_IF(text, Medic)
    else STRINGTOJOB_IF(text, Sniper)
    else STRINGTOJOB_IF(text, Spy)
    else STRINGTOJOB_IF(text, Android)
    else STRINGTOJOB_IF(text, DogRobot)
    */
    else return CharType::Unknown;
}

sf::String CharRoleToStr(CharRole role)
{
    #define ROLETOSTRING_CASE(ROLE) case CharRole::ROLE: return #ROLE;

    switch(role)
    {
    ROLETOSTRING_CASE(Hero)
    ROLETOSTRING_CASE(Boss)
    ROLETOSTRING_CASE(Target)
    ROLETOSTRING_CASE(Guest)
    ROLETOSTRING_CASE(Escort)
    default:
        return "None";
    }
}

CharRole StrToCharRole(const sf::String& text)
{
    #define STRINGTOROLE_IF(TEXT, ROLE) if (TEXT == #ROLE) return CharRole::ROLE;

         STRINGTOROLE_IF(text, Hero)
    else STRINGTOROLE_IF(text, Boss)
    else STRINGTOROLE_IF(text, Target)
    else STRINGTOROLE_IF(text, Guest)
    else STRINGTOROLE_IF(text, Escort)
    else return CharRole::None;
}
