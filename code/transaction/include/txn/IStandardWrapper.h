#ifndef _TXN_I_STANDARD_WRAPPER_H
#define _TXN_I_STANDARD_WRAPPER_H

#include <memory>

#include "txn/StandardPayload.h"
#include "txn/StandardService.h"
#include "txn/Status.h"

namespace txn {

class IStandardWrapper {
public:
  virtual Status invokeStandard(StandardService& service, StandardPayload& payload) = 0;
  virtual std::shared_ptr<StandardService> createService() = 0;
};

} // namespace txn

#endif // _TXN_I_STANDARD_WRAPPER_H