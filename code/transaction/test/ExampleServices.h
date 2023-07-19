#include "txn/Registry.h"
#include "txn/StandardPayload.h"
#include "txn/StandardService.h"
#include "txn/Status.h"
#include "txn/TokenPayload.h"
#include "txn/TokenService.h"

class ServiceA : public txn::StandardService {
public:
  txn::Status methodA(txn::StandardPayload& payload);
  txn::Status methodB(txn::StandardPayload& payload);
};

class ServiceB : public txn::TokenService {
public:
  txn::Status methodA(txn::TokenPayload& payload);
  txn::Status methodB(txn::TokenPayload& payload);
};

class ServiceC : public txn::StandardService {
public:
  ServiceC();
  ~ServiceC();

  txn::Status methodA(txn::StandardPayload& payload);

private:
  std::string _internalString;
};

extern "C"
bool registerServices(txn::Registry registry);