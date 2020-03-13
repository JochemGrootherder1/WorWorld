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

void Message::updatePositions(std::array<unsigned short, 6>& newPositions, std::array<std::string, 6>& servoTypes) {
    messageContents.clear();
    for(std::size_t i = 0; i < newPositions.size(); i++) {
        std::pair<std::string, std::pair<short, short> > position(servoTypes.at(i), std::make_pair<short, short>(newPositions.at(i), -1));
        addMessageContent(position);
    }
}

void Message::convertDegreeToPWM(Machine& machine) 
{
    for(std::map<std::string, std::pair<short, short> >::iterator it = messageContents.begin(); it != messageContents.end(); it++) {
        short servo = 0;
        if(it->first == "Base") {
            servo = 0;
        } else if (it->first == "Shoulder") {
            servo = 1;
        } else if (it->first == "Elbow") {
            servo = 2;
        } else if (it->first == "Wrist") {
            servo = 3;
        } else if (it->first == "Gripper") {
            servo = 4;
        } else if (it->first == "Wrist Rotate") {
            servo = 5;
        }

        short pwmDifference = machine.getPWMBoundaries().at(servo).second - machine.getPWMBoundaries().at(servo).first;
        std::cout << pwmDifference << std::endl;
        float multiplier = (float) pwmDifference / (degreesBoudaries.at(servo).second - degreesBoudaries.at(servo).first);
        std::cout << multiplier << std::endl;
        std::cout << it->second.first << std::endl;
        short degrees = it->second.first;
        if(degrees >= 0 && degreesBoudaries.at(servo).first < 0) {
            degrees = degrees + (-1 * degreesBoudaries.at(servo).first);
        } else if(degrees >= 0 && degreesBoudaries.at(servo).first >= 0) {
            degrees = degrees - (degreesBoudaries.at(servo).first);
        } else if (degrees < 0) {
            degrees = (-1 * degreesBoudaries.at(servo).first) - (-1 * degrees);
        }
        
        short pwm = round(multiplier * degrees + machine.getPWMBoundaries().at(servo).first);
        std::cout << pwm << std::endl;
        it->second.first = pwm;
    }
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

const MessageType Message::getMessageType() const{
    return messageType;
}
