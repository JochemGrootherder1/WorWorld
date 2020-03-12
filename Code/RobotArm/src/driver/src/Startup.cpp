#include "Startup.hpp"
#include <iostream>
#include <fstream>
#include "Moving.hpp"

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
    std::cout << "line: " << line << std::endl;
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token = "";
    std::string input = "";
    unsigned short count = 0;
    while ((pos = line.find(delimiter)) != std::string::npos)
    {
        token = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        if(input == "")
        {
            input = token;
        }
        else if(input == "park")
        {
            std::cout << "token: " << token << std::endl;
        
            machine->getParkPosition()[count] = std::stoi(token);
            ++count;
        }
        else if(input == "straightUp")
        {
            machine->getStraightUpPosition()[count] = std::stoi(token);
            ++count;
        }
        else if(input == "ready")
        {
            machine->getReadyPosition()[count] = std::stoi(token);
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
    }
    else
    {
        /*
        * FOUTMELDING OMDAT CONFIG NIET BESTAAT
         */ 
    }

    machine->setCurrentState(std::make_shared<Moving>(machine));
    

}



const std::string& Startup::getName()
{
    return name;
}