#include "RegistryImpl.h"

namespace txn {

RegistryImpl::RegistryImpl() {}
RegistryImpl::~RegistryImpl() {}

void RegistryImpl::registerStandard(const std::string& serviceName, std::shared_ptr<IStandardWrapper> pWrapper) {
  this->_standardMap[serviceName] = pWrapper;
}

Status RegistryImpl::invokeStandard(const std::string& serviceName, const StandardPayload& payload) {
  // TODO: C++20 replace std::map::find() by std::map::contains()
  if (this->_standardMap.find(serviceName) == this->_standardMap.end()) {
    // service not found, return early
    // TODO: add error handling
    return Status(1, "service not found");
  }
  IStandardWrapper* pStandardWrapper = this->_standardMap[serviceName].get();
  std::shared_ptr<Service> pService = pStandardWrapper->createService();
  return pStandardWrapper->invokeStandard(*pService, payload);
}

void RegistryImpl::registerToken(const std::string& serviceName, std::shared_ptr<ITokenWrapper> pWrapper) {
  this->_tokenMap[serviceName] = pWrapper;
}

Status RegistryImpl::invokeToken(const std::string& serviceName, const TokenPayload& payload) {
  // TODO: C++20 replace std::map::find() by std::map::contains()
  if (this->_tokenMap.find(serviceName) == this->_tokenMap.end()) {
    // service not found, return early
    // TODO: add error handling
    return Status(1, "service not found");
  }
  ITokenWrapper* pTokenWrapper = this->_tokenMap[serviceName].get();
  std::shared_ptr<Service> pService = pTokenWrapper->createService();
  return pTokenWrapper->invokeToken(*pService, payload);
}

} // namespace txn