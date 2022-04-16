#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <signal.h>

#include "../utils.h"
#include "OrderBeverageHandler.h"

using json = nlohmann::json;
using apache::thrift::server::TThreadedServer;
using apache::thrift::transport::TServerSocket;
using apache::thrift::transport::TFramedTransportFactory;
using apache::thrift::protocol::TBinaryProtocolFactory;

using namespace vending_machine;


// signal handler code
void sigintHandler(int sig) {
	exit(EXIT_SUCCESS);
}

// entry of this service
int main(int argc, char **argv) {
  // 1: notify the singal handler if interrupted
  signal(SIGINT, sigintHandler);
  // 1.1: Initialize logging
  init_logger();


  // 2: read the config file for ports and addresses
  json config_json;
  if (load_config_file("config/service-config.json", &config_json) != 0) {
    exit(EXIT_FAILURE);
  }

  // 3: get my port
  int my_port = config_json["order-beverage-service"]["port"];

  // 4: get the weather service's port and address
  int weather_service_port = config_json["weather-service"]["port"];
  std::string weather_service_addr = config_json["weather-service"]["addr"];
  
  int beverage_service_port = config_json["beverage-preference-service"]["port"];
  std::string beverage_service_addr = config_json["beverage-preference-service"]["addr"];
 
  // 5: get the client of weather-service
  ClientPool<ThriftClient<WeatherServiceClient>> weather_client_pool(
      "weather-service", weather_service_addr, weather_service_port, 0, 128, 1000);
	  
  ClientPool<ThriftClient<BeveragePreferenceServiceClient>> beverage_client_pool(
      "beverage-preference-service", beverage_service_addr, beverage_service_port, 0, 128, 1000);
	  
	  
  // 6: configure this server
  TThreadedServer server(
      std::make_shared<OrderBeverageServiceProcessor>(
          std::make_shared<OrderBeverageServiceHandler>(
              &weather_client_pool,&beverage_client_pool)),
      std::make_shared<TServerSocket>("0.0.0.0", my_port),
      std::make_shared<TFramedTransportFactory>(),
      std::make_shared<TBinaryProtocolFactory>()
  );
  
  // 7: start the server
  std::cout << "Starting the order-beverage server ..." << std::endl;
  server.serve();
  return 0;
}

