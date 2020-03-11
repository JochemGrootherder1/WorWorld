// this file is used to mock the motion planner
#include "ros/ros.h"
#include "robot_arm/ArmMessage.h"
#include <string>

int main(int argc, char** argv) {
    ros::init(argc, argv, "motion_planner");

    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<robot_arm::ArmMessage>("messages");

    while(true) {
        robot_arm::ArmMessage srv;
        std::string message;
        std::cout << "enter message: " <<  std::endl;
        std::getline(std::cin, message);
        std::cout << message << std::endl;
        srv.request.message = message;
        client.call(srv);
    }

    return 0;
}