#include "Message.hpp"
#include <iostream>

Message::Message() : messageType(None) {

}

Message::~Message() {

}

void Message::addMessageContent(const std::pair<std::string, std::pair<short, short> >& values) {
    std::cout << values.first << " " << values.second.first << " " << values.second.second << std::endl;
    messageContents.insert(values);
}

std::map<std::string, std::pair<short, short>>& Message::getMessageContents() {
    return messageContents;
}

bool Message::setMessageType(MessageType type) {
    if(messageType == None || messageType == type) { 
        messageType = type;
        return true;
    }
    return false;
}

MessageType Message::getMessageType() {
    return messageType;
}