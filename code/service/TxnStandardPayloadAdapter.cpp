#include "TxnStandardPayloadAdapter.h"

namespace svc {

TxnStandardPayloadAdapter::TxnStandardPayloadAdapter(StandardPayload payload)
    : StandardPayload(payload.data()) {
  this->setServiceName(payload.serviceName());
}

TxnStandardPayloadAdapter::TxnStandardPayloadAdapter(txn::StandardPayload payload)
    : StandardPayload(payload.data()) {
  this->setServiceName(payload.serviceName());
}

TxnStandardPayloadAdapter::~TxnStandardPayloadAdapter() {}

txn::StandardPayload TxnStandardPayloadAdapter::asTxnStandardPayload() {
  txn::StandardPayload payload(this->data());
  payload.setServiceName(this->serviceName());
  return payload;
}

} // namespace svc