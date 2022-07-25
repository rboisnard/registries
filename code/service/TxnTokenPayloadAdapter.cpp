#include "TxnTokenPayloadAdapter.h"

namespace svc {

TxnTokenPayloadAdapter::TxnTokenPayloadAdapter(TokenPayload payload)
    : TokenPayload(payload.data(), payload.token()) {
  this->setServiceName(payload.serviceName());
}

TxnTokenPayloadAdapter::TxnTokenPayloadAdapter(txn::TokenPayload payload)
    : TokenPayload(payload.data(), payload.token()) {
  this->setServiceName(payload.serviceName());
}

TxnTokenPayloadAdapter::~TxnTokenPayloadAdapter() {}

txn::TokenPayload TxnTokenPayloadAdapter::asTxnTokenPayload() {
  txn::TokenPayload payload(this->data(), this->token());
  payload.setServiceName(this->serviceName());
  return payload;
}

} // namespace svc