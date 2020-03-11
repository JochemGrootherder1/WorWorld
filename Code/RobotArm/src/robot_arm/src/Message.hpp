#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <map>
#include <string>

enum MessageType {
    None,
    Position,
    Config,
    EmergencyStop,
    PreprogrammedPosition
};

class Message {
    public:
        Message();
        virtual ~Message();
        void addMessageContent(const std::pair<std::string, std::pair<short, short> >& values);
        const std::map<std::string, std::pair<short, short>>& getMessageContents() const;
        bool setMessageType(MessageType type);
        MessageType getMessageType();
    private:
        MessageType messageType;
        std::map<std::string, std::pair<short, short>> messageContents;
};

#endif