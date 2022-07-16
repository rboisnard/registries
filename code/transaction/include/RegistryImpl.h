#ifndef _REGISTRY_IMPL_H
#define _REGISTRY_IMPL_H

#include <map>
#include <string>

#include "txn/IRegistry.h"

namespace txn {

class RegistryImpl : public IRegistry {
public:
  void registerStandard(const std::string& serviceName, std::shared_ptr<IStandardWrapper> pWrapper) override;
  void invokeStandard(const std::string serviceName, const StandardPayload& payload) override;
  void registerToken(const std::string& serviceName, std::shared_ptr<ITokenWrapper> pWrapper) override;
  void invokeToken(const std::string serviceName, const TokenPayload& payload) override;

private:
  std::map<std::string, std::shared_ptr<IStandardWrapper>> _standardMap;
  std::map<std::string, std::shared_ptr<ITokenWrapper>> _tokenMap;
};

} // namespace txn

#endif // _REGISTRY_IMPL_H