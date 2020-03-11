#include "Moving.hpp"
#include <sstream>
#include <chrono>
#include "Park.hpp"
#include "Idle.hpp"

std::map<unsigned short, std::pair<short, short>> PWMBoudaries = 
    {
        {std::make_pair(0, std::make_pair(500, 2000))},
        {std::make_pair(1, std::make_pair(500, 2000))},
        {std::make_pair(2, std::make_pair(500, 2000))},
        {std::make_pair(3, std::make_pair(500, 2000))},
        {std::make_pair(4, std::make_pair(500, 2000))},
        {std::make_pair(5, std::make_pair(500, 2000))},
    };


Moving::Moving(Machine* machine, std::map<std::string, std::pair< short, short>>& positions): State(machine), positionToMoveTo(positions)
{

}

Moving::~Moving()
{

}

unsigned short Moving::checkPWM(const unsigned short& joint,const short& PWM)
{
    if(PWMBoudaries.at(joint).first > PWM) return PWMBoudaries.at(joint).first;
    else if(PWMBoudaries.at(joint).second < PWM) return PWMBoudaries.at(joint).second;
    return PWM;
}

std::string Moving::inputToCommand()
{
    std::stringstream ss;
    newPosition = currentPosition;
    for(const auto& pair : positionToMoveTo)
    {
        unsigned short duration = defaultDuration;
        unsigned short joint = 0;
        ss << "#";
        if(pair.first == "Base") joint = 0;
        if(pair.first == "Shoulder") joint =  1;
        if(pair.first == "Elbow") joint = 2;
        if(pair.first == "Wrist") joint = 3;
        if(pair.first == "Gripper") joint = 4;
        if(pair.first == "WristRotate") joint = 5;
        ss << joint << " ";
        unsigned short PWM = checkPWM(joint, pair.second.first);
        ss << PWM << " ";
        if(pair.second.second > 0) duration = pair.second.second;
        ss << duration;
        if(duration > longestDuration) longestDuration = duration;
        newPosition[joint] = PWM;
    }
    return ss.str();
}

void Moving::doActivity()
{
    std::string command = inputToCommand();
    machine->messageSender.sendMessage(command);
    std::clock_t start = std::clock();
    std::clock_t currentTime = std::clock();
    while(1000 * (currentTime - start) / CLOCKS_PER_SEC < longestDuration){
        currentTime = std::clock();
    }
    if(newPosition == parkPosition)
    {
        currentPosition = parkPosition;
        machine->setCurrentState(std::make_shared<Park>(machine));
    }
    else
    {
        currentPosition = newPosition;
        machine->setCurrentState(std::make_shared<Idle>(machine));
    }

}

const std::string& Moving::getName()
{
    return name;
}