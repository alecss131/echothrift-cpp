#include <iostream>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include "Greet.h"

class GreetHandler : virtual public tutorial::GreetIf {
public:
    void ping() override {
        std::cout << "ping" << std::endl;
    }

    void sayHello(std::string& ret, const std::string& message) override {
        std::cout << "received message:" << message << std::endl;
        ret = message;
    }
};

int main() {
    std::cout << "Server started..." << std::endl;
    int port{9090};
    auto handler{std::make_shared<GreetHandler>()};
    auto processor{std::make_shared<tutorial::GreetProcessor>(handler)};
    auto serverTransport{std::make_shared<apache::thrift::transport::TServerSocket>(port)};
    auto transportFactory{std::make_shared<apache::thrift::transport::TBufferedTransportFactory>()};
    auto protocolFactory{std::make_shared<apache::thrift::server::TBinaryProtocolFactory>()};
    apache::thrift::server::TSimpleServer server{processor, serverTransport, transportFactory, protocolFactory};
    server.serve();
    return 0;
}