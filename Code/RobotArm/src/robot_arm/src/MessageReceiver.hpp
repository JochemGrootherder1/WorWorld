#ifndef MESSAGERECEIVER_HPP
#define MESSAGERECEIVER_HPP

#include "MessageHandler.hpp"
#include "robot_arm/ArmMessage.h"

class MessageReceiver {
    public:
        MessageReceiver();
        virtual ~MessageReceiver();
        void startServer();
    private:
        MessageHandler messageHandler;
};

bool handleMessageReceived(robot_arm::ArmMessage::Request &req, robot_arm::ArmMessage::Response &res);

#endif