#ifndef _SVC_I_REGISTRY_H
#define _SVC_I_REGISTRY_H

#include "svc/IStandardWrapper.h"
#include "svc/ITokenWrapper.h"
#include "svc/Status.h"

namespace svc {

class IRegistry {
public:
  virtual ~IRegistry() = default;
  virtual void registerService(const std::string& serviceName, std::shared_ptr<IStandardWrapper> pWrapper) = 0;
  virtual Status invoke(const std::string& serviceName, StandardPayload& payload) = 0;
  virtual void registerService(const std::string& serviceName, std::shared_ptr<ITokenWrapper> pWrapper) = 0;
  virtual Status invoke(const std::string& serviceName, TokenPayload& payload) = 0;
};

} // namespace svc

#endif // _SVC_I_REGISTRY_H