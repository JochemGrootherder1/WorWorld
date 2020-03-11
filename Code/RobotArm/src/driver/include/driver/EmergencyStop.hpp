#ifndef EMERGENCYSTOP_HPP
#define EMERGENCYSTOP_HPP

#include "States.hpp"

class EmergencyStop : public State
{
    public:
        EmergencyStop(Machine* machine);
        virtual~ EmergencyStop();
        void doActivity();
        const std::string& getName();

    private:
        std::string name = "EmergencyStop";
};

#endif