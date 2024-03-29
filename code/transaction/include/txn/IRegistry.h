#ifndef _TXN_I_REGISTRY_H
#define _TXN_I_REGISTRY_H

#include <memory>

#include "txn/IStandardWrapper.h"
#include "txn/ITokenWrapper.h"

namespace txn {

class IRegistry {
public:
  virtual ~IRegistry() = default;
  virtual void registerStandard(const std::string& serviceName, std::shared_ptr<IStandardWrapper> pWrapper) = 0;
  virtual Status invokeStandard(const std::string& serviceName, StandardPayload& payload) = 0;
  virtual void registerToken(const std::string& serviceName, std::shared_ptr<ITokenWrapper> pWrapper) = 0;
  virtual Status invokeToken(const std::string& serviceName, TokenPayload& payload) = 0;
};

} // namespace txn

#endif // _TXN_I_REGISTRY_H