#ifndef STATES_HPP
#define STATES_HPP
#include "ros/ros.h"
#include "MessageSender.hpp"
#include <array>
#include <iostream>
#include <memory>
#include <list>
#include <map>

enum DefaultPositions {
    ParkPosition,
    StraightPosition,
    ReadyPosition
};

class State;

class Machine
{
    public:
        Machine(const std::string& file);
        void setCurrentState(const std::shared_ptr<State>& aState);
        void run();
        /**
         * @brief 
         * vector[0]
         * @param eventString 
         */
        void move(std::map<std::string, std::pair<short, short>>& positions);
        void emergencyStop();
        void turnOff();
        std::string getCurrentState();
        MessageSender& getMessageSender();
        bool getStop();
        std::array<unsigned short, 6>& getDefaultPosition(DefaultPositions defaultPosition);
        std::array<unsigned short, 6>& getParkPosition();
        std::array<unsigned short, 6>& getStraightUpPosition();
        std::array<unsigned short, 6>& getReadyPosition();
        const std::map<unsigned short, std::pair<short, short>>& getPWMBoundaries() const;
    private:
        bool stop;
        MessageSender messageSender;
        std::string configFile ="";
        std::shared_ptr<State> currentState;
        std::array<unsigned short, 6> parkPosition;
        std::array<unsigned short, 6> straightUpPosition;
        std::array<unsigned short, 6> readyPosition;
        std::map<unsigned short, std::pair<short, short>> PWMBoundaries = 
        {
            {std::make_pair(0, std::make_pair(500, 2500))},
            {std::make_pair(1, std::make_pair(800, 1833))},
            {std::make_pair(2, std::make_pair(500, 2000))},
            {std::make_pair(3, std::make_pair(500, 2500))},
            {std::make_pair(4, std::make_pair(500, 2500))},
            {std::make_pair(5, std::make_pair(500, 2500))},
        };
};

class State
{
    public:
        State(Machine* aMachine) : machine(aMachine){}
        virtual ~State(){}
        virtual void doActivity() = 0; 
        virtual const std::string& getName() = 0;
        bool getFinished();
        void setFinished();
    protected:
        Machine* machine;
        bool finished = false;
        std::array<unsigned short, 6> currentPosition;
        std::array<unsigned short, 6> newPosition;
};



#endif