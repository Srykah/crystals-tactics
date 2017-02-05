#ifndef STATEDATA_HPP_INCLUDED
#define STATEDATA_HPP_INCLUDED

#include "../Data/GameDataIdentifiers.hpp"
#include "../Other/pugixml.hpp"
#include <string>

/*//

StateData

Cette union contient les donn�es dont peuvent avoir besoin les �crans
sp�cifiques. Par exemple, l'�cran de bataille a besoin du fichier contenant
les donn�es sur la bataille. L'union contient aussi les donn�es �chang�es
entre les �crans : par exemple, une bo�te de dialogue se servira d'un
bool�en pour faire savoir si l'utilisateur a accept�.

//*/

class Character;

class StateData
{
private:
    union DataUnion
    {
        Missions::ID            missionID;
        int                     integer;
        bool                    boolean;
        pugi::xml_node*         node;
    };

public:
    enum DataType
    {
        None,
        MissionID,
        Integer,
        Boolean,
        CharacSPtr,
        Node,
        Str
    };

public:
    StateData();
    StateData(Missions::ID missionID);
    StateData(int integer);
    StateData(Character* characSPtr);
    StateData(bool boolean);
    StateData(pugi::xml_node& node);
    StateData(const std::string& str);
    ~StateData();

    DataType getDataType() const;

    void setMissionID(Missions::ID missionID);
    Missions::ID missionID() const;

    void setInteger(int integer);
    int integer() const;

    void setCharacPtr(Character* characSPtr);
    Character* characSPtr() const;

    void setBoolean(bool boolean);
    bool boolean() const;

    void setNode(pugi::xml_node& node);
    pugi::xml_node node() const;

    void setStr(const std::string& str);
    const std::string& str() const;

private:
    DataType mDataType;
    DataUnion mDataUnion;
    Character* mCharac;
    std::string mStr;
};

#endif // STATEDATA_HPP_INCLUDED
