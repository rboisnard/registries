#include "TxnStatusAdapter.h"

namespace svc {

TxnStatusAdapter::TxnStatusAdapter(Status status)
    : Status(status.code(), status.message()) {}

TxnStatusAdapter::TxnStatusAdapter(int code)
    : Status(code) {}

TxnStatusAdapter::TxnStatusAdapter(int code, const std::string& message)
    : Status(code, message) {}

txn::Status TxnStatusAdapter::asTxnStatus() {
  return txn::Status(this->_code, this->_message);
}

} // namespace svc