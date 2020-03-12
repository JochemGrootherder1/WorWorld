#ifndef MESSAGEHANDLER_HPP
#define MESSAGEHANDLER_HPP

#include "Message.hpp"
#include "driver/States.hpp"
#include <queue>
#include <array>
#include <thread>
#include <mutex>

class MessageHandler {
    public:
        MessageHandler();
        virtual ~MessageHandler();
        void updateMessagePositions(Message& message);
        void parseMessage(const std::string& input);
        void handleMessages();

    private:
        std::thread messageHandler;
        std::mutex messagesMutex;
        std::queue<Message> messages; 
        std::array<std::string, 6> allowedServoTypes {
            "Base", "Shoulder", "Elbow", "Wrist", "Gripper", "Wrist Rotate"
        };
        std::array<std::string, 5> allowedMessageTypes {
            "Park", "Ready", "Straight-up", "EmergencyStop", "Offset"
        };
        Machine machine;
};

#endif