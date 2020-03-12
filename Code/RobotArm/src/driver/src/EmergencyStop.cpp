#include "EmergencyStop.hpp"

EmergencyStop::EmergencyStop(Machine* machine): State(machine)
{
    std::cout << "EMERGENCY STOP" << std::endl;
    machine->getMessageSender().emergencyStop();
}

EmergencyStop::~EmergencyStop()
{

}

void EmergencyStop::doActivity()
{
    
}

const std::string& EmergencyStop::getName()
{
    return name;
}