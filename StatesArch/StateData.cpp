#include "../StatesArch/StateData.hpp"

StateData::StateData()
: mDataType(StateData::None)
{

}

StateData::StateData(Missions::ID missionID)
: mDataType(StateData::MissionID)
{
    mDataUnion.missionID = missionID;
}

StateData::StateData(int integer)
: mDataType(StateData::Str)
{
    mDataUnion.integer = integer;
}

StateData::StateData(Character* characSPtr)
: mDataType(StateData::CharacSPtr)
{
    mCharac = characSPtr;
}

StateData::StateData(bool boolean)
: mDataType(StateData::Boolean)
{
    mDataUnion.boolean = boolean;
}

StateData::StateData(pugi::xml_node& node)
: mDataType(StateData::Node)
{
    mDataUnion.node = &node;
}

StateData::StateData(const std::string& str)
: mDataType(StateData::Str)
, mStr(str)
{

}

StateData::~StateData()
{

}

StateData::DataType StateData::getDataType() const
{
    return mDataType;
}

void StateData::setMissionID(Missions::ID missionID)
{
    mDataUnion.missionID = missionID;
    mDataType = MissionID;
}

Missions::ID StateData::missionID() const
{
    return mDataUnion.missionID;
}

void StateData::setInteger(int integer)
{
    mDataUnion.integer = integer;
    mDataType = Integer;
}

int StateData::integer() const
{
    return mDataUnion.integer;
}

void StateData::setCharacPtr(Character* characSPtr)
{
    mCharac = characSPtr;
    mDataType = CharacSPtr;
}

Character* StateData::characSPtr() const
{
    return mCharac;
}

void StateData::setBoolean(bool boolean)
{
    mDataUnion.boolean = boolean;
    mDataType = Boolean;
}

bool StateData::boolean() const
{
    return mDataUnion.boolean;
}

void StateData::setNode(pugi::xml_node& node)
{
    mDataUnion.node = &node;
    mDataType = Node;
}

pugi::xml_node StateData::node() const
{
    return *mDataUnion.node;
}

void StateData::setStr(const std::string& str)
{
    mStr = str;
    mDataType = Str;
}

const std::string& StateData::str() const
{
    return mStr;
}
