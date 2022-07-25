#ifndef _TXN_I_TOKEN_WRAPPER_H
#define _TXN_I_TOKEN_WRAPPER_H

#include "txn/Status.h"
#include "txn/TokenPayload.h"
#include "txn/TokenService.h"

namespace txn {

class ITokenWrapper {
public:
  virtual Status invokeToken(TokenService& service, TokenPayload& payload) = 0;
  virtual std::shared_ptr<TokenService> createService() = 0;
};

} // namespace txn

#endif // _TXN_I_TOKEN_WRAPPER_H