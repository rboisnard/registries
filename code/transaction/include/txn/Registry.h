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
  void registerStandard(const std::string& serviceName, Status (T::*method)(StandardPayload&));

  Status invokeStandard(const std::string& serviceName, StandardPayload& payload);

  template <typename T>
  void registerToken(const std::string& serviceName, Status (T::*method)(TokenPayload&));

  Status invokeToken(const std::string& serviceName, TokenPayload& payload);

private:
  template <class> class StandardWrapper;
  template <class> class TokenWrapper;
  std::shared_ptr<IRegistry> _pImpl;
};

// template for standard payload services
template <typename T>
class Registry::StandardWrapper : public IStandardWrapper {
public:
  StandardWrapper(Status (T::*method)(StandardPayload&)) : _method(method) {}

  std::shared_ptr<StandardService> createService() {
    return std::make_shared<T>();
  }

protected:
  Status invokeStandard(StandardService& service, StandardPayload& payload) {
    return (static_cast<T&>(service).*_method)(payload);
  }

  Status (T::*_method)(StandardPayload&);
};

template <typename T>
inline void Registry::registerStandard(const std::string& serviceName, Status (T::*method)(StandardPayload&)) {
  this->_pImpl->registerStandard(serviceName, std::make_shared<StandardWrapper<T>>(method));
}

// template for token payload services
template <typename T>
class Registry::TokenWrapper : public ITokenWrapper {
public:
  TokenWrapper(Status (T::*method)(TokenPayload&)) : _method(method) {}

  std::shared_ptr<TokenService> createService() {
    return std::make_shared<T>();
  }

protected:
  Status invokeToken(TokenService& service, TokenPayload& payload) {
    return (static_cast<T&>(service).*_method)(payload);
  }

  Status (T::*_method)(TokenPayload&);
};

template <typename T>
inline void Registry::registerToken(const std::string& serviceName, Status (T::*method)(TokenPayload&)) {
  this->_pImpl->registerToken(serviceName, std::make_shared<TokenWrapper<T>>(method));
}

// other definitions
typedef bool (*initializer_t)(Registry&);
typedef bool (*finalizer_t)();

} // namespace txn

#endif // _TXN_REGISTRY_H