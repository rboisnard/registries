#ifndef _TXN_STATUS_ADAPTER_H
#define _TXN_STATUS_ADAPTER_H

#include "txn/Status.h"

#include "svc/Status.h"

namespace svc {

class TxnStatusAdapter : public Status {
public:
  explicit TxnStatusAdapter(Status status);
  explicit TxnStatusAdapter(int code);
  TxnStatusAdapter(int code, const std::string& message);
  ~TxnStatusAdapter() = default;
  txn::Status asTxnStatus();
};

} // namespace svc

#endif // _TXN_STATUS_ADAPTER_H