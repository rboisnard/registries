#ifndef _SVC_REGISTRY_H
#define _SVC_REGISTRY_H

#include <algorithm>
#include <memory>
#include <type_traits>

#include "txn/Registry.h"

#include "svc/IRegistry.h"
#include "svc/IStandardWrapper.h"
#include "svc/ITokenWrapper.h"

namespace svc {

namespace internal {

template <std::size_t N>
struct StringLiteral {
  constexpr StringLiteral(const char (&literal)[N]) {
    std::copy_n(literal, N, _value);
  }
  char _value[N];
};

template <auto START, auto END, auto INC>
constexpr void constexpr_for(auto f) {
  if constexpr (START < END) {
    f(std::integral_constant<decltype(START), START>());
    constexpr_for<START + INC, END, INC>(f);
  }
}

template<auto END>
constexpr void constexpr_for(auto f) {
  constexpr_for<0, END, 1>(f);
}

template <int I, class... Ts>
constexpr decltype(auto) get(Ts&&... ts) {
  return std::get<I>(std::forward_as_tuple(ts...));
}

} // namespace internal

class Registry {
public:
  explicit Registry();
  ~Registry();

  template <typename T, internal::StringLiteral LIT>
  void registerService(Status (T::*method)(const std::string& serviceName, StandardPayload& payload));
  template <typename T, internal::StringLiteral... LITS>
  void registerServices(Status (T::*method)(const std::string& serviceName, StandardPayload& payload));
  txn::Status invoke(const std::string& serviceName, txn::StandardPayload& payload);

  template <typename T, internal::StringLiteral LIT>
  void registerService(Status (T::*method)(const std::string& serviceName, TokenPayload& payload));
  template <typename T, internal::StringLiteral... LITS>
  void registerServices(Status (T::*method)(const std::string& serviceName, TokenPayload& payload));
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
  StandardWrapper(Status (T::*method)(const std::string& serviceName, StandardPayload& payload)) : _method(method) {}

  std::shared_ptr<Service> createService() {
    return std::make_shared<T>();
  }

protected:
  Status invoke(Service& service, const std::string& serviceName, StandardPayload& payload) {
    return (static_cast<T&>(service).*_method)(serviceName, payload);
  }

  Status (T::*_method)(const std::string& serviceName, StandardPayload& payload);
};

template <typename T, internal::StringLiteral LIT>
inline void Registry::registerService(Status (T::*method)(const std::string& serviceName, StandardPayload& payload)) {

  class TxnService : public txn::StandardService {
  public:
    txn::Status invoke(txn::StandardPayload& payload) {
      const std::string& serviceName(LIT._value);
      return registryInstance.invoke(serviceName, payload);
    }
  };

  const std::string& serviceName(LIT._value);
  this->_pImpl->registerService(serviceName, std::make_shared<StandardWrapper<T>>(method));
  this->_txnRegistry.registerStandard<TxnService>(serviceName, &TxnService::invoke);
}

template <typename T, internal::StringLiteral... LITS>
inline void Registry::registerServices(Status (T::*method)(const std::string& serviceName, StandardPayload& payload)){
  internal::constexpr_for<sizeof...(LITS)>([this, &method](auto i){
    this->registerService<T, internal::get<i>(LITS...)>(method);
  });
}

// template for token wrapper implementation
template <typename T>
class Registry::TokenWrapper : public ITokenWrapper {
public:
  TokenWrapper(Status (T::*method)(const std::string& serviceName, TokenPayload& payload)) : _method(method) {}

  std::shared_ptr<Service> createService() {
    return std::make_shared<T>();
  }

protected:
  Status invoke(Service& service, const std::string& serviceName, TokenPayload& payload) {
    return (static_cast<T&>(service).*_method)(serviceName, payload);
  }

  Status (T::*_method)(const std::string& serviceName, TokenPayload& payload);
};

template <typename T, internal::StringLiteral LIT>
inline void Registry::registerService(Status (T::*method)(const std::string& serviceName, TokenPayload& payload)) {

  class TxnService : public txn::TokenService {
  public:
    txn::Status invoke(txn::TokenPayload& payload) {
      const std::string& serviceName(LIT._value);
      return registryInstance.invoke(serviceName, payload);
    }
  };

  const std::string& serviceName(LIT._value);
  this->_pImpl->registerService(serviceName, std::make_shared<TokenWrapper<T>>(method));
  this->_txnRegistry.registerToken<TxnService>(serviceName, &TxnService::invoke);
}

template <typename T, internal::StringLiteral... LITS>
void Registry::registerServices(Status (T::*method)(const std::string& serviceName, TokenPayload& payload)) {
  internal::constexpr_for<sizeof...(LITS)>([this, &method](auto i){
    this->registerService<T, internal::get<i>(LITS...)>(method);
  });
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