#ifndef PARK_HPP
#define PARK_HPP

#include "States.hpp"

class Park : public State
{
    public:
        Park(Machine* machine);
        virtual~ Park();
        void doActivity();
        const std::string& getName();

    private:
        std::string name = "park";
};

#endif