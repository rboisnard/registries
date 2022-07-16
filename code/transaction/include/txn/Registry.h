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
  void registerStandard(const std::string serviceName, void (T::*method)(const StandardPayload&));

  void invokeStandard(const std::string serviceName, const StandardPayload& payload);

  template <typename T>
  void registerToken(const std::string serviceName, void (T::*method)(const TokenPayload&));

  void invokeToken(const std::string serviceName, const TokenPayload& payload);

private:
  std::unique_ptr<IRegistry> _pImpl;
};

// template for standard payload services
template <typename T>
class StandardWrapper : IStandardWrapper {
public:
  StandardWrapper(void (T::*method)(const StandardPayload&)) : _method(method) {}

  void invokeStandard(const StandardPayload& payload) {
    T service;
    service.*_method(payload);
  }

private:
  void (T::*_method)(const StandardPayload&);
};

template <typename T>
void Registry::registerStandard(const std::string serviceName, void (T::*method)(const StandardPayload&)) {
  this->_pImpl->registerStandard(serviceName, new StandardWrapper(T::method));
}

// template for token payload services
template <typename T>
class TokenWrapper : ITokenWrapper {
public:
  TokenWrapper(void (T::*method)(const TokenPayload&)) : _method(method) {}

  void invokeToken(const TokenPayload& payload) {
    T service;
    service.*_method(payload);
  }

private:
  void (T::*_method)(const TokenPayload&);
};

template <typename T>
void Registry::registerToken(const std::string serviceName, void (T::*method)(const TokenPayload&)) {
  this->_pImpl->registerToken(serviceName, new TokenWrapper(T::method));
}

// other definitions
typedef void (*initializer_t)(Registry&);

} // namespace txn

#endif // _TXN_REGISTRY_H