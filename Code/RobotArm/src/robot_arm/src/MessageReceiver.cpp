#include "MessageReceiver.hpp"
#include "ros/ros.h"

MessageReceiver::MessageReceiver(MessageHandler* messageHandler) : messageHandler(messageHandler) {

}

MessageReceiver::~MessageReceiver() {

}

bool MessageReceiver::handleMessageReceived(robot_arm::ArmMessage::Request &req, robot_arm::ArmMessage::Response &res) {
    messageHandler->parseMessage(req.message);
    return true;
}

void MessageReceiver::startServer() {
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("messages", &MessageReceiver::handleMessageReceived, this);
    
    ros::spin();
}
