#include "svc/Registry.h"
#include "RegistryImpl.h"

namespace svc {

Registry::Registry() {
  _pImpl = std::shared_ptr<IRegistry>(new RegistryImpl());
}
Registry::~Registry() {}

txn::Status Registry::invoke(const std::string& serviceName, Payload_t payload) {
  return this->_pImpl->invoke(serviceName, payload);
}

} // namespace svc