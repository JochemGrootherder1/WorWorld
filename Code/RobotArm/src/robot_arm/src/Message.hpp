#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "driver/States.hpp"
#include <map>
#include <string>

enum MessageType {
    None,
    Position,
    Config,
    PreprogrammedPosition
};

class Message {
    public:
        Message();
        virtual ~Message();
        void addMessageContent(const std::pair<std::string, std::pair<short, short> >& values);
        void updatePositions(std::array<unsigned short, 6>& newPositions, std::array<std::string, 6>& servoTypes);
        void convertDegreeToPWM(Machine& machine);
        std::map<std::string, std::pair<short, short>>& getMessageContents();
        bool setMessageType(MessageType type);
        const MessageType getMessageType() const;

    private:
        MessageType messageType;
        std::map<std::string, std::pair<short, short>> messageContents;
        std::map<unsigned short, std::pair<short, short>> degreesBoudaries = 
        {
            {std::make_pair(0, std::make_pair(-90, 90))},
            {std::make_pair(1, std::make_pair(90, -30))},
            {std::make_pair(2, std::make_pair(0, 135))},
            {std::make_pair(3, std::make_pair(-90, 90))},
            {std::make_pair(4, std::make_pair(-90, 90))},
            {std::make_pair(5, std::make_pair(-90, 90))},
        };
};

#endif