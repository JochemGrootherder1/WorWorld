#include "Idle.hpp"

Idle::Idle(Machine* machine): State(machine)
{

}

Idle::~Idle()
{

}

void Idle::doActivity()
{
    
}


const std::string& Idle::getName()
{
    return name;
}