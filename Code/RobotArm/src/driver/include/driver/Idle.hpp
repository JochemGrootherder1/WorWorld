#ifndef IDLE_HPP
#define IDLE_HPP

#include "States.hpp"


class Idle : public State
{
    public:
        Idle(Machine* machine);
        virtual~ Idle();
        void doActivity();
        const std::string& getName();

    private:
        std::string name = "idle";
};

#endif