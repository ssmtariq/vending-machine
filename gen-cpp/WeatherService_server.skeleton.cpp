// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "WeatherService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace  ::vending_machine;

class WeatherServiceHandler : virtual public WeatherServiceIf {
 public:
  WeatherServiceHandler() {
    // Your initialization goes here
  }

  WeatherType::type GetWeather(const int64_t city) {
    // Your implementation goes here
    printf("GetWeather\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  ::std::shared_ptr<WeatherServiceHandler> handler(new WeatherServiceHandler());
  ::std::shared_ptr<TProcessor> processor(new WeatherServiceProcessor(handler));
  ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

