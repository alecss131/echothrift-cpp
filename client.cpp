#include <iostream>
#include <string>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include "Greet.h"

int main(int argc, char** argv) {
    int port{9090};
    auto socket{std::make_shared<apache::thrift::transport::TSocket>("localhost", port)};
    auto transport{std::make_shared<apache::thrift::transport::TBufferedTransport>(socket)};
    auto protocol{std::make_shared<apache::thrift::protocol::TBinaryProtocol>(transport)};
    tutorial::GreetClient client{protocol};
    try {
        transport->open();

        client.ping();
        std::cout << "ping()" << std::endl;

        std::string message{argc == 2 ? argv[1] : "Hello, World!"};
        std::string res{};
        std::cout << "sent message: " << message << std::endl;
        client.sayHello(res, message);
        std::cout << "received message: " << res << std::endl;

        transport->close();
    } catch (apache::thrift::TException& tx) {
        std::cout << "ERROR: " << tx.what() << std::endl;
    }
}
