#ifndef MOVING_HPP
#define MOVING_HPP

#include "States.hpp"

class Moving : public State
{
    public:
        Moving(Machine* machine, std::map<std::string, std::pair<short, short>>& positions);
        virtual~ Moving();
        void doActivity();
        std::string inputToCommand();
        const std::string& getName();
        unsigned short checkPWM(const unsigned short& joint, const short& PWM);
    private:
        std::string name = "moving";
        std::map<std::string, std::pair<short, short>> positionToMoveTo;
        unsigned short defaultDuration = 1000;
        unsigned short longestDuration = 0;
};

#endif