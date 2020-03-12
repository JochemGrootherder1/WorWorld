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

void Message::updatePositions(std::array<unsigned short, 6>& newPositions, std::array<std::string, 6>& servoTypes) {
    messageContents.clear();
    for(std::size_t i = 0; i < newPositions.size(); i++) {
        std::pair<std::string, std::pair<short, short> > position(servoTypes.at(i), std::make_pair<short, short>(newPositions.at(i), -1));
        addMessageContent(position);
    }
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

short Message::convertDegreeToPWM(const short& degree) 
{   
    return int(float(degree+90) / 0.09) + 500;
}