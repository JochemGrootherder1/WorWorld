#include "ros/ros.h"

#include "MessageReceiver.hpp"

int main(int argc, char** argv) {
    ros::init(argc, argv, "Highleveldriver");

    MessageHandler messageHandler;
    MessageReceiver messageReceiver(&messageHandler);
    messageReceiver.startServer();
}