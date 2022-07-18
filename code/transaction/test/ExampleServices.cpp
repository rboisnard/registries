#include <sstream>

#include "ExampleServices.h"

txn::Status ServiceA::methodA(const txn::StandardPayload& payload) {
  std::stringstream stream;
  stream << "serviceA:methodA:" << payload.data() << ":-";
  return txn::Status(0, stream.str());
}

txn::Status ServiceA::methodB(const txn::StandardPayload& payload) {
  std::stringstream stream;
  stream << "serviceA:methodB:" << payload.data() << ":-";
  return txn::Status(0, stream.str());
}

txn::Status ServiceB::methodA(const txn::StandardPayload& payload) {
  std::stringstream stream;
  stream << "serviceB:methodA:" << payload.data() << ":-";
  return txn::Status(0, stream.str());
}

txn::Status ServiceB::methodB(const txn::TokenPayload& payload) {
  std::stringstream stream;
  stream << "serviceB:methodB:" << payload.data() << ":" << payload.token() << ":-";
  return txn::Status(0, stream.str());
}

ServiceC::ServiceC()
    : txn::Service(), _internalString("internal") {}

ServiceC::~ServiceC() {}

txn::Status ServiceC::methodA(const txn::StandardPayload& payload) {
  std::stringstream stream;
  stream << "serviceC:methodA:" << payload.data() << ":" << this->_internalString << ":-";
  return txn::Status(0, stream.str());
}

extern "C"
void registerServices(txn::Registry registry) {
  registry.registerStandard<ServiceA>("serv1", &ServiceA::methodA);
  registry.registerStandard<ServiceA>("serv2", &ServiceA::methodB);
  registry.registerStandard<ServiceB>("serv3", &ServiceB::methodA);
  registry.registerToken<ServiceB>("serv4", &ServiceB::methodB);
  registry.registerStandard<ServiceC>("serv5", &ServiceC::methodA);
}