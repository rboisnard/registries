#include "TxnTokenPayloadAdapter.h"

namespace svc {

TxnTokenPayloadAdapter::TxnTokenPayloadAdapter(TokenPayload payload)
    : TokenPayload(payload.data(), payload.token()) {}

TxnTokenPayloadAdapter::TxnTokenPayloadAdapter(txn::TokenPayload payload)
    : TokenPayload(payload.data(), payload.token()) {}

TxnTokenPayloadAdapter::~TxnTokenPayloadAdapter() {}

txn::TokenPayload TxnTokenPayloadAdapter::asTxnTokenPayload() {
  return txn::TokenPayload(this->data(), this->token());
}

} // namespace svc