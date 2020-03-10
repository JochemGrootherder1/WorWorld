#include "States.hpp"
#include "Calibrate.hpp"
#include "EmergencyStop.hpp"
#include "Idle.hpp"
#include "Moving.hpp"
#include "Park.hpp"
#include "Startup.hpp"

Machine::Machine(const std::string& file) : configFile(file)
{
    std::cout << "BBB"  << std::endl; 
}

void Machine::setCurrentState(std::shared_ptr<State> aState)
{
    currentState = aState;
    currentState->doActivity();
}

void Machine::run()
{
    if(currentState->getName != "EmergencyStop") setCurrentState(std::make_shared<Startup>(this, configFile));
}

void Machine::move(std::map<std::string, std::pair<short, short>>& positions)
{
    if(currentState->getName() != "EmergencyStop" || currentState->getName() != "startUp") 
    {
        setCurrentState(std::make_shared<Moving>(this, positions));
        currentState->doActivity();
    }
}

void Machine::emergencyStop()
{
    messageSender.emergencyStop();
    setCurrentState(std::make_shared<EmergencyStop>(this));
}

void Machine::turnOff()
{
    if(currentState->getName() == "park")
        std::exit(0);
}