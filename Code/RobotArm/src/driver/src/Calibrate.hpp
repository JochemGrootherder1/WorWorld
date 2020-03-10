#ifndef CALIBRATE_HPP
#define CALIBRATE_HPP

#include "States.hpp"

class Calibrate : public State
{
    public:
        Calibrate(Machine* machine, std::string file);
        virtual~ Calibrate();
        void doActivity();
        const std::string& getName();
    private:
        std::string name = "Calibrate";
        bool calibrated;
        std::string configFile;
};

#endif