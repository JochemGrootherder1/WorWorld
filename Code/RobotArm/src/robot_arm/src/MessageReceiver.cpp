#include "MessageReceiver.hpp"
#include "ros/ros.h"

MessageReceiver::MessageReceiver() {

}

MessageReceiver::~MessageReceiver() {

}

bool handleMessageReceived(robot_arm::ArmMessage::Request &req, robot_arm::ArmMessage::Response &res) {

}

void MessageReceiver::startServer() {
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("add_two_ints", handleMessageReceived);
    ROS_INFO("Ready to add two ints.");
    ros::spin();
}