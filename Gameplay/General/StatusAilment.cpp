#include "Gameplay/General/StatusAilment.hpp"

sf::String SAToStr(StatusAilment ailment)
{
    switch(ailment)
    {
    case StatusAilment::Burnt:
        return "Burnt";
    case StatusAilment::Poisoned:
        return "Poisoned";
    case StatusAilment::Bleeding:
        return "Bleeding";
    case StatusAilment::Rooted:
        return "Rooted";
    case StatusAilment::Disabled:
        return "Disabled";
    case StatusAilment::Asleep:
        return "Asleep";
    case StatusAilment::Invisible:
        return "Invisible";
        /*
    case StatusAilment::AtkPlus:
        return "AtkPlus";
    case StatusAilment::DefPlus:
        return "DefPlus";
    case StatusAilment::RangePlus:
        return "RangePlus";
    case StatusAilment::MobilityPlus:
        return "MobilityPlus";
        */

    default:
        return "None";
    }
}

SA StrToSA(const sf::String& text)
{
    if (text == "Burnt") return StatusAilment::Burnt;
    else if (text == "Poisoned") return StatusAilment::Poisoned;
    else if (text == "Bleeding") return StatusAilment::Bleeding;
    else if (text == "Rooted") return StatusAilment::Rooted;
    else if (text == "Disabled") return StatusAilment::Disabled;
    else if (text == "Asleep") return StatusAilment::Asleep;
    else if (text == "Invisible") return StatusAilment::Invisible;
    else return StatusAilment::None;
}
