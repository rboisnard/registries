#ifndef _TXN_STANDARD_PAYLOAD_ADAPTER_H
#define _TXN_STANDARD_PAYLOAD_ADAPTER_H

#include "txn/StandardPayload.h"

#include "svc/StandardPayload.h"

namespace svc {

class TxnStandardPayloadAdapter : public StandardPayload {
public:
  explicit TxnStandardPayloadAdapter(StandardPayload payload);
  explicit TxnStandardPayloadAdapter(txn::StandardPayload payload);
  ~TxnStandardPayloadAdapter();
  txn::StandardPayload asTxnStandardPayload();
};

} // namespace svc

#endif // _TXN_STANDARD_PAYLOAD_ADAPTER_H