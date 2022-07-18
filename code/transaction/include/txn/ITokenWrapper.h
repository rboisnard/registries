#ifndef _TXN_I_TOKEN_WRAPPER_H
#define _TXN_I_TOKEN_WRAPPER_H

#include "txn/Service.h"
#include "txn/Status.h"
#include "txn/TokenPayload.h"

namespace txn {

class ITokenWrapper {
public:
  virtual Status invokeToken(Service& service, const TokenPayload& payload) = 0;
  virtual std::shared_ptr<Service> createService() = 0;
};

} // namespace txn

#endif // _TXN_I_TOKEN_WRAPPER_H