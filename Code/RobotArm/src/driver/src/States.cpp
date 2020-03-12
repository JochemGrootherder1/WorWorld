#include "States.hpp"
#include "Calibrate.hpp"
#include "EmergencyStop.hpp"
#include "Idle.hpp"
#include "Moving.hpp"
#include "Park.hpp"
#include "Startup.hpp"

Machine::Machine(const std::string& file) : stop(false), configFile(file)
{
    std::cout << "BBB"  << std::endl; 
}

void Machine::setCurrentState(const std::shared_ptr<State>& aState)
{
    // we check before every action if the other thread did set a stop sign
    currentState = aState;
    
    if(!stop)
        currentState->doActivity();
    
    if(stop) {
        stop = false; // we handled the stop message
        if(currentState->getName() != "EmergencyStop") {
            setCurrentState(std::make_shared<EmergencyStop>(this));
        }
    }
    
    currentState->setFinished();
}

void Machine::run()
{
    setCurrentState(std::make_shared<Startup>(this, configFile));
}

void Machine::move(std::map<std::string, std::pair<short, short>>& positions)
{
    if(currentState->getName() != "EmergencyStop" && currentState->getName() != "startUp") 
    {
        std::cout << currentState->getName() << std::endl;
        std::cout << "switching" << std::endl;
        setCurrentState(std::make_shared<Moving>(this, positions));
    }
}

void Machine::emergencyStop()
{
    if(currentState->getName() != "EmergencyStop") {
        if(!currentState->getFinished())
            stop = true;
        else
            setCurrentState(std::make_shared<EmergencyStop>(this));
    }
}

void Machine::turnOff()
{
    if(currentState->getName() == "park")
        std::exit(0);
}

MessageSender& Machine::getMessageSender() {
    return messageSender;
}

bool Machine::getStop() {
    return stop;
}

void State::setFinished() {
    finished = true;
}

bool State::getFinished() {
    return finished;
}