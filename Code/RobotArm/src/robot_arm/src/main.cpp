#include "ros/ros.h"

#include "MessageReceiver.hpp"

int main(int argc, char** argv) {
    ros::init(argc, argv, "High level driver");

    MessageReceiver messageReceiver;
    messageReceiver.startServer();
}