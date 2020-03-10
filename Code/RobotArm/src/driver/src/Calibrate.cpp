#include "Calibrate.hpp"
#include <fstream>

Calibrate::Calibrate(Machine* machine, std::string file): State(machine), configFile(file)
{
    std::cout << "CALIBRATE CONSTRUCTOR" << std::endl;
}
Calibrate::~Calibrate()
{

}

void Calibrate::doActivity()
{
    std::ofstream myFile;
    myFile.open(configFile, std::ios::trunc);
    myFile << "CONFIGFILE CREATED" << std::endl;
    myFile.close();
}

const std::string& Calibrate::getName()
{
    return name;
}