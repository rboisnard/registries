#ifndef _TXN_TOKEN_PAYLOAD_ADAPTER_H
#define _TXN_TOKEN_PAYLOAD_ADAPTER_H

#include "txn/TokenPayload.h"

#include "svc/TokenPayload.h"

namespace svc {

class TxnTokenPayloadAdapter : public TokenPayload {
public:
  explicit TxnTokenPayloadAdapter(TokenPayload payload);
  explicit TxnTokenPayloadAdapter(txn::TokenPayload payload);
  ~TxnTokenPayloadAdapter();
  txn::TokenPayload asTxnTokenPayload();
};

} // namespace svc

#endif // _TXN_TOKEN_PAYLOAD_ADAPTER_H