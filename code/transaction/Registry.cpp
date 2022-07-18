#include "txn/Registry.h"
#include "RegistryImpl.h"

namespace txn {

Registry::Registry() {
  _pImpl = std::shared_ptr<IRegistry>(new RegistryImpl());
}
Registry::~Registry() {}

Status Registry::invokeStandard(const std::string& serviceName, const StandardPayload& payload) {
  return this->_pImpl->invokeStandard(serviceName, payload);
}

Status Registry::invokeToken(const std::string& serviceName, const TokenPayload& payload) {
  return this->_pImpl->invokeToken(serviceName, payload);
}

} // namespace txn