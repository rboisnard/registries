#ifndef _TXN_REGISTRY_H
#define _TXN_REGISTRY_H

#include <memory>

#include "txn/IRegistry.h"
#include "txn/IStandardWrapper.h"
#include "txn/ITokenWrapper.h"

namespace txn {

class Registry {
public:
  Registry();
  ~Registry();

  template <typename T>
  void registerStandard(const std::string& serviceName, Status (T::*method)(const StandardPayload&));

  Status invokeStandard(const std::string& serviceName, const StandardPayload& payload);

  template <typename T>
  void registerToken(const std::string& serviceName, Status (T::*method)(const TokenPayload&));

  Status invokeToken(const std::string& serviceName, const TokenPayload& payload);

private:
  template <class> class StandardWrapper;
  template <class> class TokenWrapper;
  std::shared_ptr<IRegistry> _pImpl;
};

// template for standard payload services
template <typename T>
class Registry::StandardWrapper : public IStandardWrapper {
public:
  StandardWrapper(Status (T::*method)(const StandardPayload&)) : _method(method) {}

  std::shared_ptr<Service> createService() {
    return std::make_shared<T>();
  }

protected:
  Status invokeStandard(Service& service, const StandardPayload& payload) {
    return (static_cast<T&>(service).*_method)(payload);
  }

  Status (T::*_method)(const StandardPayload&);
};

template <typename T>
inline void Registry::registerStandard(const std::string& serviceName, Status (T::*method)(const StandardPayload&)) {
  this->_pImpl->registerStandard(serviceName, std::make_shared<StandardWrapper<T>>(method));
}

// template for token payload services
template <typename T>
class Registry::TokenWrapper : public ITokenWrapper {
public:
  TokenWrapper(Status (T::*method)(const TokenPayload&)) : _method(method) {}

  std::shared_ptr<Service> createService() {
    return std::make_shared<T>();
  }

protected:
  Status invokeToken(Service& service, const TokenPayload& payload) {
    return (static_cast<T&>(service).*_method)(payload);
  }

  Status (T::*_method)(const TokenPayload&);
};

template <typename T>
inline void Registry::registerToken(const std::string& serviceName, Status (T::*method)(const TokenPayload&)) {
  this->_pImpl->registerToken(serviceName, std::make_shared<TokenWrapper<T>>(method));
}

// other definitions
typedef void (*initializer_t)(Registry&);

} // namespace txn

#endif // _TXN_REGISTRY_H