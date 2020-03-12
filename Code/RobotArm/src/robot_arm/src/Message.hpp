#ifndef MESSAGE_HPP
#define MESSAGE_HPP

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
        std::map<std::string, std::pair<short, short>>& getMessageContents();
        bool setMessageType(MessageType type);
        const MessageType getMessageType() const;
    private:
        MessageType messageType;
        std::map<std::string, std::pair<short, short>> messageContents;
};

#endif