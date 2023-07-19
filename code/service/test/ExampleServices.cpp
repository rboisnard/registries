#include <sstream>
#include <string>
#include <vector>

#include "ExampleServices.h"

svc::Status ServiceA::methodA([[maybe_unused]] const std::string& serviceName, svc::StandardPayload& payload) {
  std::stringstream stream;
  stream << "serviceA2:methodA2:" << payload.data() << ":-";
  return svc::Status(0, stream.str());
}

svc::Status ServiceA::methodB([[maybe_unused]] const std::string& serviceName, svc::StandardPayload& payload) {
  std::stringstream stream;
  stream << "serviceA2:methodB2:" << payload.data() << ":-";
  return svc::Status(0, stream.str());
}

svc::Status ServiceB::methodA([[maybe_unused]] const std::string& serviceName, svc::StandardPayload& payload) {
  std::stringstream stream;
  stream << "serviceB2:methodA2:" << payload.data() << ":-";
  return svc::Status(0, stream.str());
}

svc::Status ServiceB::methodB([[maybe_unused]] const std::string& serviceName, svc::TokenPayload& payload) {
  std::stringstream stream;
  stream << "serviceB2:methodB2:" << payload.data() << ":" << payload.token() << ":-";
  return svc::Status(0, stream.str());
}

ServiceC::ServiceC()
    : svc::Service(), _internalString("internal") {}

ServiceC::~ServiceC() {}

svc::Status ServiceC::methodA([[maybe_unused]] const std::string& serviceName, svc::StandardPayload& payload) {
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
  registry.registerServices<ServiceA, "serv1", "serv2">(&ServiceA::methodA);
  registry.registerServices<ServiceA, "serv3", "serv4">(&ServiceA::methodB);
  registry.registerServices<ServiceB, "serv5", "serv6">(&ServiceB::methodA);
  registry.registerServices<ServiceB, "serv7", "serv8">(&ServiceB::methodB);
  registry.registerServices<ServiceC, "serv9">(&ServiceC::methodA);
  return true;
}

extern "C"
bool finalizeServices() {
  return true;
}