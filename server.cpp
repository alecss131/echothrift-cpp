#include <iostream>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include "Greet.h"

class GreetHandler : virtual public GreetIf {
public:
    void sayHello(HelloReply& reply, const HelloRequest& req) override {
        const std::string &name{req.name};
        std::cout << "New client request with name: " << name << std::endl;
        std::string message{"Hello, " + name + "!"};
        reply.message = message;
    }
};

int main() {
    std::cout << "Server started..." << std::endl;
    int port{9090};
    auto handler{std::make_shared<GreetHandler>()};
    auto processor{std::make_shared<GreetProcessor>(handler)};
    auto serverTransport{std::make_shared<apache::thrift::transport::TServerSocket>(port)};
    auto transportFactory{std::make_shared<apache::thrift::transport::TBufferedTransportFactory>()};
    auto protocolFactory{std::make_shared<apache::thrift::server::TBinaryProtocolFactory>()};
    apache::thrift::server::TSimpleServer server{processor, serverTransport, transportFactory, protocolFactory};
    server.serve();
    return 0;
}