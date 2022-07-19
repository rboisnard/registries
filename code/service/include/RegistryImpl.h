#ifndef _REGISTRY_IMPL_H
#define _REGISTRY_IMPL_H

#include <map>

#include "svc/IRegistry.h"

namespace svc {

class RegistryImpl : public IRegistry {
public:
  RegistryImpl();
  ~RegistryImpl();

  void registerCallback(ServiceList_t serviceNames, std::shared_ptr<ICallbackWrapper> pWrapper) override;
  txn::Status invoke(const std::string& serviceName, Payload_t payload) override;

private:
  std::map<std::string, std::shared_ptr<ICallbackWrapper>> _callbackMap;
};

} // namespace svc

#endif // _REGISTRY_IMPL_H