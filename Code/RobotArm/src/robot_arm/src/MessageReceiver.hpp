#ifndef MESSAGERECEIVER_HPP
#define MESSAGERECEIVER_HPP

#include "MessageHandler.hpp"
#include "robot_arm/ArmMessage.h"

class MessageReceiver {
    public:
        MessageReceiver(MessageHandler* messageHandler);
        virtual ~MessageReceiver();
        void startServer();
        bool handleMessageReceived(robot_arm::ArmMessage::Request &req, robot_arm::ArmMessage::Response &res);
    private:
        MessageHandler* messageHandler;
};

#endif