#ifndef MESSAGESENDER_HPP
#define MESSAGESENDER_HPP

#include <string>
#include <boost/asio.hpp>

class MessageSender {
public:
	MessageSender();
	virtual ~MessageSender();

    //SendMessage wordt vervangen door een action -> 
    void sendMessage(const std::string& message);
    void emergencyStop();

private:
    boost::asio::io_service ioservice;
    //poortnaam
    boost::asio::serial_port serial;
};

#endif
