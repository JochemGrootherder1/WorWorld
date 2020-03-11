#include "MessageHandler.hpp"
#include "driver/States.hpp"
#include <iostream>

MessageHandler::MessageHandler() : messageHandler(&MessageHandler::handleMessages, this){

}

MessageHandler::~MessageHandler() {

}

void MessageHandler::parseMessage(const std::string& input) {
    Message message;
    std::pair<std::string, std::pair<short, short>> messageContent(std::string(), std::pair<short, short>(0, -1));
    bool finished = false;
    bool firstValue = true;
    unsigned short currentValue = 0;
    char delimitter = ':';
    char commandSplitter = ';';
    std::size_t startPosition = 0;
    std::size_t delimmiterPosition;
    std::size_t commandEndPosition;

    while(!finished) {
        std::string inputToParse;
        delimmiterPosition = input.find(delimitter, startPosition);
        commandEndPosition = input.find(commandSplitter, startPosition);
        bool toggleFirstValue = false;
        
        if(delimmiterPosition == std::string::npos && commandEndPosition == std::string::npos) {
            inputToParse = input.substr(startPosition, std::string::npos);
            finished = true;
        } else if(commandEndPosition != std::string::npos && commandEndPosition < delimmiterPosition) {
            inputToParse = input.substr(startPosition, commandEndPosition - startPosition);
            startPosition = commandEndPosition + 1;
            toggleFirstValue = true;
        } else if (delimmiterPosition != std::string::npos) {
            inputToParse = input.substr(startPosition, delimmiterPosition - startPosition);
            startPosition = delimmiterPosition + 1;
        }

        if(inputToParse.length() > 0) {
            if(firstValue) {
                bool found = false;
                std::size_t maxSize = allowedMessageTypes.size() > allowedServoTypes.size() ? allowedMessageTypes.size() : allowedServoTypes.size();
                for(std::size_t i = 0; i < maxSize; i++) {
                    if(i < allowedServoTypes.size() && allowedServoTypes.at(i) == inputToParse) {
                        found = true;
                        if(!message.setMessageType(Position)) {
                            return;
                        }
                        break;
                    } else if(i < allowedMessageTypes.size() && allowedMessageTypes.at(i) == inputToParse) {
                        found = true;
                        if(inputToParse == "Ready" || inputToParse == "Straight-up" || inputToParse == "Park") {
                            if(!message.setMessageType(PreprogrammedPosition)) {
                                return;
                            }
                        } else if (inputToParse == "EmergencyStop") {
                            if(!message.setMessageType(EmergencyStop)) {
                                return;
                            }
                        } else if (inputToParse == "Offset") {
                            if(!message.setMessageType(Config)) {
                                return;
                            }
                        }
                        break;
                    }
                }

                if(found) {
                    messageContent.first = inputToParse;
                } else {
                    return;
                }
                firstValue = false;
            } else {
                for(std::size_t i = 0; i < inputToParse.length(); i++) {
                    if(!isdigit(inputToParse.at(i)) && (inputToParse.at(i) != '-' || inputToParse.at(i) == '-' && i > 0)) {
                        return;
                    }
                }
                if(currentValue == 0) {
                    messageContent.second.first = std::stoi(inputToParse);
                    currentValue++;
                } else {
                    messageContent.second.second = std::stoi(inputToParse);
                }
            }
        } else {
            break;
        }

        if(toggleFirstValue || finished) {
            message.addMessageContent(messageContent);
            currentValue = 0;
            firstValue = true;
            messageContent = std::pair<std::string, std::pair<short, short> >(std::string(), std::pair<short, short>(0, -1));
        }
    }

    {
        std::lock_guard<std::mutex> lock(messagesMutex);
        messages.push(message);
    }
}

void MessageHandler::handleMessages() {
    while(true) {
        messagesMutex.lock();
        if(messages.size() > 0) {
            if(messages.front().getMessageType() == Position) {
                std::cout << "position" << std::endl;
                messagesMutex.unlock();
                // call position function
            } else if (messages.front().getMessageType() == PreprogrammedPosition) {
                std::cout << "preprogrammed position" << std::endl;
                messagesMutex.unlock();
            } else if(messages.front().getMessageType() == EmergencyStop) {
                std::cout << "emergency stop" << std::endl;
                messagesMutex.unlock();
                
            } else {
                messagesMutex.unlock();
            }

            {
                std::lock_guard<std::mutex> lock(messagesMutex);
                messages.pop();
            }
        } else {
            messagesMutex.unlock();
        }
    }
}