#ifndef _REGISTRY_IMPL_H
#define _REGISTRY_IMPL_H

#include <map>

#include "svc/IRegistry.h"

namespace svc {

class RegistryImpl : public IRegistry {
public:
  RegistryImpl();
  ~RegistryImpl();

  void registerService(ServiceList serviceNames, std::shared_ptr<IStandardWrapper> pWrapper) override;
  Status invoke(const std::string& serviceName, StandardPayload& payload) override;
  void registerService(ServiceList serviceNames, std::shared_ptr<ITokenWrapper> pWrapper) override;
  Status invoke(const std::string& serviceName, TokenPayload& payload) override;

private:
  std::map<std::string, std::shared_ptr<IStandardWrapper>> _standardMap;
  std::map<std::string, std::shared_ptr<ITokenWrapper>> _tokenMap;
};

} // namespace svc

#endif // _REGISTRY_IMPL_H