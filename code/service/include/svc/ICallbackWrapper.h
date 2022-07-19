#ifndef _SVC_I_CALLBACK_WRAPPER_H
#define _SVC_I_CALLBACK_WRAPPER_H

#include <memory>

#include "txn/Status.h"

#include "svc/Callback.h"
#include "svc/Payload.h"

namespace svc {

class ICallbackWrapper {
public:
  virtual txn::Status invoke(Callback& callback, Payload_t payload) = 0;
  virtual std::shared_ptr<Callback> createCallback(std::shared_ptr<txn::Service> pService) = 0;
};

} // namespace svc

#endif // _SVC_I_CALLBACK_WRAPPER_H