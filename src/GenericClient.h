#ifndef VENDING_MACHINE_MICROSERVICES_GENERICCLIENT_H
#define VENDING_MACHINE_MICROSERVICES_GENERICCLIENT_H

#include <string>

namespace vending_machine {

class GenericClient{
 public:
  virtual ~GenericClient() = default;
  virtual void Connect() = 0;
  virtual void KeepAlive() = 0;
  virtual void KeepAlive(int) = 0;
  virtual void Disconnect() = 0;
  virtual bool IsConnected() = 0;

 protected:
  std::string _addr;
  int _port;
};

} // namespace vending_machine

#endif //VENDING_MACHINE_MICROSERVICES_GENERICCLIENT_H
