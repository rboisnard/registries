#ifndef _SVC_REGISTRY_H
#define _SVC_REGISTRY_H

#include <memory>

#include "svc/IRegistry.h"
#include "svc/ICallbackWrapper.h"

namespace svc {

class Registry {
public:
  Registry();
  ~Registry();

  template <typename T>
  void registerCallback(ServiceList_t serviceNames, txn::Status (T::*method)(const txn::StandardPayload& payload));

  template <typename T>
  void registerCallback(ServiceList_t serviceNames, txn::Status (T::*method)(const txn::TokenPayload& payload));

  txn::Status invoke(const std::string& serviceName, Payload_t payload);

  private:
    template <class> class StandardWrapper;
    template <class> class TokenWrapper;
    std::shared_ptr<IRegistry> _pImpl;
};

// template for standard wrapper implementation
template <typename T>
class Registry::StandardWrapper : public ICallbackWrapper {
public:
  StandardWrapper(txn::Status (T::*method)(const txn::StandardPayload& payload)) : _method(method) {}

  std::shared_ptr<Callback> createCallback(std::shared_ptr<txn::Service> pService) {
    return std::make_shared<T>(pService);
  }

protected:
  txn::Status invoke(Callback& callback, Payload_t payload) {
    if (std::holds_alternative<const txn::StandardPayload&>(payload)) {
      return (static_cast<T&>(callback.service()).*_method)(std::get<const txn::StandardPayload&>(payload));
    }
    // wrong payload type
    // TODO: add error handling
    return txn::Status(1, "wrong payload type");
  }

  txn::Status (T::*_method)(const txn::StandardPayload& payload);
};

template <typename T>
inline void Registry::registerCallback(ServiceList_t serviceNames, txn::Status (T::*method)(const txn::StandardPayload& payload)) {
  this->_pImpl->registerCallback(serviceNames, std::make_shared<StandardWrapper<T>>(method));
}

// template for token wrapper implementation
template <typename T>
class Registry::TokenWrapper : public ICallbackWrapper {
public:
  TokenWrapper(txn::Status (T::*method)(const txn::TokenPayload& payload)) : _method(method) {}

  std::shared_ptr<Callback> createCallback(std::shared_ptr<txn::Service> pService) {
    return std::make_shared<T>(pService);
  }

protected:
  txn::Status invoke(Callback& callback, Payload_t payload) {
    if (std::holds_alternative<const txn::TokenPayload&>(payload)) {
      return (static_cast<T&>(callback.service()).*_method)(std::get<const txn::TokenPayload&>(payload));
    }
    // wrong payload type
    // TODO: add error handling
    return txn::Status(1, "wrong payload type");
  }

  txn::Status (T::*_method)(const txn::TokenPayload& payload);
};

template <typename T>
inline void Registry::registerCallback(ServiceList_t serviceNames, txn::Status (T::*method)(const txn::TokenPayload& payload)) {
  this->_pImpl->registerCallback(serviceNames, std::make_shared<TokenWrapper<T>>(method));
}

// other definitions
typedef void (*initializer_t)(Registry&);

} // namespace svc

#endif // _SVC_REGISTRY_H