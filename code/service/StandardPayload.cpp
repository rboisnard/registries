#include "svc/StandardPayload.h"

namespace svc {

StandardPayload::StandardPayload(const std::string data)
    : _data(data) {}
StandardPayload::~StandardPayload() {}

const std::string StandardPayload::data() const { return this->_data; }

} // namespace svc