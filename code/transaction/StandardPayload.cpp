#include "txn/StandardPayload.h"

namespace txn {

StandardPayload::StandardPayload(const std::string data)
    : _data(data) {}
StandardPayload::~StandardPayload() {}

const std::string StandardPayload::data() const {
  return this->_data;
}

} // namespace txn