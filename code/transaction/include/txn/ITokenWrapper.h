#ifndef _TXN_I_TOKEN_WRAPPER_H
#define _TXN_I_TOKEN_WRAPPER_H

#include "txn/Service.h"
#include "txn/TokenPayload.h"

namespace txn {

class ITokenWrapper {
public:
  virtual void invokeToken(const TokenPayload& payload) = 0;
  //virtual Service makeInstance() = 0;
};

} // namespace txn

#endif // _TXN_I_TOKEN_WRAPPER_H