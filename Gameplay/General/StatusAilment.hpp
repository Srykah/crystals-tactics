#ifndef STATUSAILMENT_HPP_INCLUDED
#define STATUSAILMENT_HPP_INCLUDED

enum StatusAilment
{
    Burnt,
    Poisoned,
    Paralysed
};

const StatusAilment BadAilments[] =
{
    Burnt,
    Poisoned,
    Paralysed
};

const StatusAilment GoodAilments[] =
{

};

struct StatusAilments
{
    void addAilment(StatusAilment ailment, int duration);
    bool hasAilment(StatusAilment ailment) const;
    int  getAilmentDuration(StatusAilment ailment) const;
    void newTurn();
    void removeAilment(StatusAilment ailment);
    void removeBadAilments();
    void removeGoodAilments();
    void clear();

    std::map< StatusAilment, int > mAilments;
};

typedef StatusAilment SA;

#endif // STATUSAILMENT_HPP_INCLUDED
