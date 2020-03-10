#include "Park.hpp"

Park::Park(Machine* machine): State(machine)
{
    std::cout << "PARK CONSTRUCTOR" << std::endl;
}


Park::~Park()
{

}

void Park::doActivity()
{

}

const std::string& Park::getName()
{
    return name;
}