#ifndef MISSIONLIST_HPP_INCLUDED
#define MISSIONLIST_HPP_INCLUDED

#include "XML/pugixml.hpp"

class MissionList
{
public:
    MissionList();
    ~MissionList();

    void save(pugi::xml_node file);

protected:

private:

};


#endif // MISSIONLIST_HPP_INCLUDED
