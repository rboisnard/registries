#include <sstream>
#include <string>
#include <vector>

#include "ExampleServices.h"

svc::Status ServiceA::methodA(svc::StandardPayload& payload) {
  std::stringstream stream;
  stream << "serviceA2:methodA2:" << payload.data() << ":-";
  return svc::Status(0, stream.str());
}

svc::Status ServiceA::methodB(svc::StandardPayload& payload) {
  std::stringstream stream;
  stream << "serviceA2:methodB2:" << payload.data() << ":-";
  return svc::Status(0, stream.str());
}

svc::Status ServiceB::methodA(svc::StandardPayload& payload) {
  std::stringstream stream;
  stream << "serviceB2:methodA2:" << payload.data() << ":-";
  return svc::Status(0, stream.str());
}

svc::Status ServiceB::methodB(svc::TokenPayload& payload) {
  std::stringstream stream;
  stream << "serviceB2:methodB2:" << payload.data() << ":" << payload.token() << ":-";
  return svc::Status(0, stream.str());
}

ServiceC::ServiceC()
    : svc::Service(), _internalString("internal") {}

ServiceC::~ServiceC() {}

svc::Status ServiceC::methodA(svc::StandardPayload& payload) {
  std::stringstream stream;
  stream << "serviceC2:methodA2:" << payload.data() << ":" << this->_internalString << ":-";
  return svc::Status(0, stream.str());
}

extern "C"
bool registerTxnServices(txn::Registry registry) {
  svc::registryInstance.setTxnRegistry(registry);
  return registerSvcServices(svc::registryInstance);
}

extern "C"
bool registerSvcServices(svc::Registry registry) {
  registry.registerService<ServiceA>({"serv1", "serv2"}, &ServiceA::methodA);
  registry.registerService<ServiceA>({"serv3", "serv4"}, &ServiceA::methodB);
  registry.registerService<ServiceB>({"serv5", "serv6"}, &ServiceB::methodA);
  registry.registerService<ServiceB>({"serv7", "serv8"}, &ServiceB::methodB);
  registry.registerService<ServiceC>({"serv9"}, &ServiceC::methodA);
  return true;
}

extern "C"
bool finalizeServices() {
  return true;
}