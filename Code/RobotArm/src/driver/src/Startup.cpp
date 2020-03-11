#include "Startup.hpp"
#include <iostream>
#include <fstream>
#include "Calibrate.hpp"
#include "Park.hpp"

Startup::Startup(Machine* machine, const std::string& inputFile) : State(machine), configFile(inputFile)
{
}

Startup::~Startup()
{

}

void Startup::doActivity()
{
    readConfiguration(configFile);
}

void Startup::parseLine(std::string line)
{
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token = "";
    std::string input = "";
    unsigned short count = 0;
    while ((pos = line.find(delimiter) != std::string::npos))
    {
        token = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        if(input == "")
        {
            input = token;
        }
        else if(input == "park")
        {
            parkPosition[count] = std::stoi(token);
            ++count;
        }
        else if(input == "straightUp")
        {
            straightUpPosition[count] = std::stoi(token);
            ++count;
        }
        else if(input == "ready")
        {
            readyPosition[count] = std::stoi(token);
            ++count;
        }
    }
}

void Startup::readConfiguration(const std::string& configFile)
{
    std::ifstream myFile(configFile);
    std::string input = "";
    if(myFile.good()){//check whether config file exists
        if(myFile.is_open())
        {
            while(std::getline(myFile, input))
            {
                parseLine(input);
            }
        }
        machine->setCurrentState(std::make_shared<Park>(machine));
    }
    else
    {
        machine->setCurrentState(std::make_shared<Calibrate>(machine, configFile));
    }
}


const std::string& Startup::getName()
{
    return name;
}