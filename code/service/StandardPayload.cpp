#include "svc/StandardPayload.h"

namespace svc {

StandardPayload::StandardPayload(const std::string data)
    : _data(data) {}

StandardPayload::~StandardPayload() {}

const std::string StandardPayload::data() const {
  return this->_data;
}

std::string StandardPayload::serviceName() {
  return this->_serviceName;
}

void StandardPayload::setServiceName(std::string serviceName) {
  this->_serviceName = serviceName;
}

} // namespace svc