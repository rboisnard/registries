#ifndef _SVC_PAYLOAD_H
#define _SVC_PAYLOAD_H

#include <variant>

#include "txn/StandardPayload.h"
#include "txn/TokenPayload.h"

namespace svc {

typedef std::variant<txn::StandardPayload, txn::TokenPayload> Payload_t;

} // namespace svc

#endif // _SVC_PAYLOAD_H