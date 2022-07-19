#ifndef _SVC_I_REGISTRY_H
#define _SVC_I_REGISTRY_H

#include <functional>
#include <memory>
#include <vector>

#include "txn/Service.h"
#include "txn/Status.h"

#include "svc/ICallbackWrapper.h"

namespace svc {

typedef std::vector<std::reference_wrapper<const std::string>> ServiceList_t;

class IRegistry : public txn::Service {
public:
  virtual ~IRegistry() = default;
  virtual void registerCallback(ServiceList_t serviceNames, std::shared_ptr<ICallbackWrapper> pWrapper) = 0;
  virtual txn::Status invoke(const std::string& serviceName, Payload_t payload) = 0;
};

} // namespace svc

#endif // _SVC_I_REGISTRY_H