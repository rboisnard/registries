#include "TxnStandardPayloadAdapter.h"

namespace svc {

TxnStandardPayloadAdapter::TxnStandardPayloadAdapter(StandardPayload payload)
    : StandardPayload(payload.data()) {}

TxnStandardPayloadAdapter::TxnStandardPayloadAdapter(txn::StandardPayload payload)
    : StandardPayload(payload.data()) {}

TxnStandardPayloadAdapter::~TxnStandardPayloadAdapter() {}

txn::StandardPayload TxnStandardPayloadAdapter::asTxnStandardPayload() {
  return txn::StandardPayload(this->data());
}

} // namespace svc