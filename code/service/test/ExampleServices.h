#include "svc/IRegistry.h"
#include "svc/Registry.h"
#include "svc/Service.h"
#include "svc/StandardPayload.h"
#include "svc/Status.h"
#include "svc/TokenPayload.h"

class ServiceA : public svc::Service {
public:
  svc::Status methodA([[maybe_unused]] const std::string& serviceName, svc::StandardPayload& payload);
  svc::Status methodB([[maybe_unused]] const std::string& serviceName, svc::StandardPayload& payload);
};

class ServiceB : public svc::Service {
public:
  svc::Status methodA([[maybe_unused]] const std::string& serviceName, svc::StandardPayload& payload);
  svc::Status methodB([[maybe_unused]] const std::string& serviceName, svc::TokenPayload& payload);
};

class ServiceC : public svc::Service {
public:
  ServiceC();
  ~ServiceC();

  svc::Status methodA([[maybe_unused]] const std::string& serviceName, svc::StandardPayload& payload);

private:
  std::string _internalString;
};

extern "C"
bool registerTxnServices(txn::Registry registry);

extern "C"
bool registerSvcServices(svc::Registry registry);

extern "C"
bool finalizeServices();