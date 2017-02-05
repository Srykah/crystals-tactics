#ifndef STATUSAILMENT_HPP_INCLUDED
#define STATUSAILMENT_HPP_INCLUDED

struct StatusAilment
{
    enum Type
    {
        Burnt,
        Poisoned,
        Paralysed,
        Asleep,
        Invisible,
        AtkPlus,
        DefPlus
    };

    StatusAilment(Type type, int duration, float effect);

    Type type;

    int duration;
    float effect;
};

#endif // STATUSAILMENT_HPP_INCLUDED
