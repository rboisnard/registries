#include "RegistryImpl.h"

namespace svc {

RegistryImpl::RegistryImpl() {}
RegistryImpl::~RegistryImpl() {}

void RegistryImpl::registerService(const std::string& serviceName, std::shared_ptr<IStandardWrapper> pWrapper) {
  this->_standardMap[serviceName] = pWrapper;
}

Status RegistryImpl::invoke(const std::string& serviceName, StandardPayload& payload) {
  if (!this->_standardMap.contains(serviceName)) {
    // service not found, return early
    // TODO: add error handling
    return Status(1, "service not found");
  }
  IStandardWrapper* pStandardWrapper = this->_standardMap[serviceName].get();
  std::shared_ptr<Service> pService = pStandardWrapper->createService();
  return pStandardWrapper->invoke(*pService, serviceName, payload);
}

void RegistryImpl::registerService(const std::string& serviceName, std::shared_ptr<ITokenWrapper> pWrapper) {
  this->_tokenMap[serviceName] = pWrapper;
}

Status RegistryImpl::invoke(const std::string& serviceName, TokenPayload& payload) {
  if (!this->_tokenMap.contains(serviceName)) {
    // service not found, return early
    // TODO: add error handling
    return Status(1, "service not found");
  }
  ITokenWrapper* pTokenWrapper = this->_tokenMap[serviceName].get();
  std::shared_ptr<Service> pService = pTokenWrapper->createService();
  return pTokenWrapper->invoke(*pService, serviceName, payload);
}

} // namespace svc