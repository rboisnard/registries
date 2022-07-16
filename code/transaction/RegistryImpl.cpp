#include "RegistryImpl.h"

namespace txn {

void RegistryImpl::registerStandard(const std::string& serviceName, std::shared_ptr<IStandardWrapper> pWrapper) {
  this->_standardMap[serviceName] = pWrapper;
}

void RegistryImpl::invokeStandard(const std::string serviceName, const StandardPayload& payload) {
  // TODO: C++20 replace std::map::find() by std::map::contains()
  if (this->_standardMap.find(serviceName) == this->_standardMap.end()) {
    // service not found, return early
    // TODO: add error handling
  }
  this->_standardMap[serviceName]->invokeStandard(payload);
}

void RegistryImpl::registerToken(const std::string& serviceName, std::shared_ptr<ITokenWrapper> pWrapper) {
  this->_tokenMap[serviceName] = pWrapper;
}

void RegistryImpl::invokeToken(const std::string serviceName, const TokenPayload& payload) {
  // TODO: C++20 replace std::map::find() by std::map::contains()
  if (this->_tokenMap.find(serviceName) == this->_tokenMap.end()) {
    // service not found, return early
    // TODO: add error handling
  }
  this->_tokenMap[serviceName]->invokeToken(payload);
}

} // namespace txn