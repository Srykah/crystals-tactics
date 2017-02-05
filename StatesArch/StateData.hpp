#ifndef STATEDATA_HPP_INCLUDED
#define STATEDATA_HPP_INCLUDED

#include "../Data/GameDataIdentifiers.hpp"
#include "../Other/pugixml.hpp"
#include <string>

/*//

StateData

Cette union contient les données dont peuvent avoir besoin les écrans
spécifiques. Par exemple, l'écran de bataille a besoin du fichier contenant
les données sur la bataille. L'union contient aussi les données échangées
entre les écrans : par exemple, une boîte de dialogue se servira d'un
booléen pour faire savoir si l'utilisateur a accepté.

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
