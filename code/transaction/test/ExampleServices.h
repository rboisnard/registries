#include "txn/Registry.h"
#include "txn/Service.h"
#include "txn/StandardPayload.h"
#include "txn/Status.h"
#include "txn/TokenPayload.h"

class ServiceA : public txn::Service {
public:
  txn::Status methodA(const txn::StandardPayload& payload);
  txn::Status methodB(const txn::StandardPayload& payload);
};

class ServiceB : public txn::Service {
public:
  txn::Status methodA(const txn::StandardPayload& payload);
  txn::Status methodB(const txn::TokenPayload& payload);
};

class ServiceC : public txn::Service {
public:
  ServiceC();
  ~ServiceC();

  txn::Status methodA(const txn::StandardPayload& payload);

private:
  std::string _internalString;
};

extern "C"
void registerServices(txn::Registry registry);