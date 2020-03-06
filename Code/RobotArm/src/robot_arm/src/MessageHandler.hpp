#ifndef MESSAGEHANDLER_HPP
#define MESSAGEHANDLER_HPP

class MessageHandler {
    public:
        MessageHandler();
        virtual ~MessageHandler();
        void parseMessage();
};

#endif