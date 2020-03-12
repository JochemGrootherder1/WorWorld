#include "EmergencyStop.hpp"

EmergencyStop::EmergencyStop(Machine* machine): State(machine)
{
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