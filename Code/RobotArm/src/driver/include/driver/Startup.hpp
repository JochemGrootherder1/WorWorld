#ifndef STARTUP_HPP
#define STARTUP_HPP

#include "States.hpp"
#include <array>

class Startup : public State
{
    public:
        Startup(Machine* machine, const std::string& configFile);
        virtual~ Startup();
        void doActivity();
        void parseLine(std::string input);
        void readConfiguration(const std::string& configFile);
        const std::string& getName();

    private:
        std::string name = "startUp";
        std::string configFile;

};

#endif