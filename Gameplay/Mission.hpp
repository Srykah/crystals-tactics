#ifndef MISSION_HPP_INCLUDED
#define MISSION_HPP_INCLUDED

#include "../StatesArch/StateRequerer.hpp"
#include <string>

class Mission : public StateRequerer
{
public:
    Mission();
    ~Mission();

    void load(const std::string& file);

private:

};


#endif // MISSION_HPP_INCLUDED
