#ifndef _SVC_I_TOKEN_WRAPPER_H
#define _SVC_I_TOKEN_WRAPPER_H

#include <memory>

#include "svc/TokenPayload.h"
#include "svc/Status.h"
#include "svc/Service.h"

namespace svc {

class ITokenWrapper {
public:
  virtual Status invoke(Service& service, const std::string& serviceName, TokenPayload& payload) = 0;
  virtual std::shared_ptr<Service> createService() = 0;
};

} // namespace svc

#endif // _SVC_I_TOKEN_WRAPPER_H