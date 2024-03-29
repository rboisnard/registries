#ifndef _SVC_I_STANDARD_WRAPPER_H
#define _SVC_I_STANDARD_WRAPPER_H

#include <memory>

#include "svc/StandardPayload.h"
#include "svc/Status.h"
#include "svc/Service.h"

namespace svc {

class IStandardWrapper {
public:
  virtual Status invoke(Service& service, const std::string& serviceName, StandardPayload& payload) = 0;
  virtual std::shared_ptr<Service> createService() = 0;
};

} // namespace svc

#endif // _SVC_I_STANDARD_WRAPPER_H