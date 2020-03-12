#ifndef MESSAGEHANDLER_HPP
#define MESSAGEHANDLER_HPP

#include "Message.hpp"
#include "driver/States.hpp"
#include <queue>
#include <array>
#include <thread>
#include <mutex>

#define NR_OF_ALLOWED_SERVO_TYPES 6
#define NR_OF_OTHER_MESSAGE_TYPES 5

struct allowedAngles {

};

class MessageHandler {
    public:
        MessageHandler();
        virtual ~MessageHandler();
        void parseMessage(const std::string& input);
        void handleMessages();

    private:
        std::thread messageHandler;
        std::mutex messagesMutex;
        std::queue<Message> messages; 
        std::array<std::string, NR_OF_ALLOWED_SERVO_TYPES> allowedServoTypes {
            "Base", "Shoulder", "Elbow", "Wrist", "Gripper", "Wrist Rotate"
        };
        std::array<std::string, NR_OF_OTHER_MESSAGE_TYPES> allowedMessageTypes {
            "Park", "Ready", "Straight-up", "EmergencyStop", "Offset"
        };
        Machine machine;
};

#endif