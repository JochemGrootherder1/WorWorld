#include "MessageSender.hpp"
#include <iostream>
#include <boost/asio.hpp>
#include <thread>

MessageSender::MessageSender() : serial(ioservice, "/dev/ttyUSB3") {

	serial.set_option(boost::asio::serial_port_base::baud_rate(9600));
	serial.set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::none));
	serial.set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::none));
	serial.set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::one));
	serial.set_option(boost::asio::serial_port::character_size(boost::asio::serial_port::character_size(8)));
}

MessageSender::~MessageSender() {
 if (serial.is_open()) {
		serial.close();
	}
}


void MessageSender::sendMessage(const std::string& message) {
    boost::asio::streambuf b;
    std::ostream os(&b);
    os << message << "\n\r";
    std::cout << message << std::endl;
    boost::asio::write(serial, b.data());
    os.flush();
}

void MessageSender::emergencyStop() {
    std::string message = "STOP 0 1 2 3 4 5";
    // send message
    sendMessage(message);
    std::cout << "sending emergency stop: " << message << std::endl;
}