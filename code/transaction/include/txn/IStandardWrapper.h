#ifndef _TXN_I_STANDARD_WRAPPER_H
#define _TXN_I_STANDARD_WRAPPER_H

#include "txn/Service.h"
#include "txn/StandardPayload.h"

namespace txn {

class IStandardWrapper {
public:
  virtual void invokeStandard(const StandardPayload& payload) = 0;
  //virtual Service makeInstance() = 0;
};

} // namespace txn

#endif // _TXN_I_STANDARD_WRAPPER_H