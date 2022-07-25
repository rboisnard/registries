#ifndef _SVC_REGISTRY_H
#define _SVC_REGISTRY_H

#include <memory>

#include "txn/Registry.h"

#include "svc/IRegistry.h"
#include "svc/IStandardWrapper.h"
#include "svc/ITokenWrapper.h"

namespace svc {

class Registry {
public:
  explicit Registry();
  ~Registry();

  template <typename T>
  void registerService(ServiceList serviceNames, Status (T::*method)(StandardPayload& payload));
  txn::Status invoke(const std::string& serviceName, txn::StandardPayload& payload);

  template <typename T>
  void registerService(ServiceList serviceNames, Status (T::*method)(TokenPayload& payload));
  txn::Status invoke(const std::string& serviceName, txn::TokenPayload& payload);

  void setTxnRegistry(txn::Registry txnRegistry);

private:
  template <typename> class StandardWrapper;
  template <typename> class TokenWrapper;
  std::shared_ptr<IRegistry> _pImpl;
  txn::Registry _txnRegistry;
};

// global unique instance
extern Registry registryInstance;

// template for standard wrapper implementation
template <typename T>
class Registry::StandardWrapper : public IStandardWrapper {
public:
  StandardWrapper(Status (T::*method)(StandardPayload& payload)) : _method(method) {}

  std::shared_ptr<Service> createService() {
    return std::make_shared<T>();
  }

protected:
  Status invoke(Service& service, StandardPayload& payload) {
    return (static_cast<T&>(service).*_method)(payload);
  }

  Status (T::*_method)(StandardPayload& payload);
};

template <typename T>
inline void Registry::registerService(ServiceList serviceNames, Status (T::*method)(StandardPayload& payload)) {

  class TxnService : public txn::StandardService {
  public:
    txn::Status invoke(txn::StandardPayload& payload) {
      return registryInstance.invoke(payload.serviceName(), payload);
    }
  };

  this->_pImpl->registerService(serviceNames, std::make_shared<StandardWrapper<T>>(method));

  for (ServiceList::iterator it = serviceNames.begin(); it != serviceNames.end(); ++it) {
    this->_txnRegistry.registerStandard<TxnService>(*it, &TxnService::invoke);
  }
}

// template for token wrapper implementation
template <typename T>
class Registry::TokenWrapper : public ITokenWrapper {
public:
  TokenWrapper(Status (T::*method)(TokenPayload& payload)) : _method(method) {}

  std::shared_ptr<Service> createService() {
    return std::make_shared<T>();
  }

protected:
  Status invoke(Service& service, TokenPayload& payload) {
    return (static_cast<T&>(service).*_method)(payload);
  }

  Status (T::*_method)(TokenPayload& payload);
};

template <typename T>
inline void Registry::registerService(ServiceList serviceNames, Status (T::*method)(TokenPayload& payload)) {

  class TxnService : public txn::TokenService {
  public:
    txn::Status invoke(txn::TokenPayload& payload) {
      return registryInstance.invoke(payload.serviceName(), payload);
    }
  };

  this->_pImpl->registerService(serviceNames, std::make_shared<TokenWrapper<T>>(method));

  for (ServiceList::iterator it = serviceNames.begin(); it != serviceNames.end(); ++it) {
    this->_txnRegistry.registerToken<TxnService>(*it, &TxnService::invoke);
  }
}

// other definitions
typedef bool (*initializer_t)(Registry&);
typedef bool (*finalizer_t)();

} // namespace svc

extern "C"
bool initLibrary(txn::Registry& registry);

extern "C"
bool closeLibrary();

#endif // _SVC_REGISTRY_H