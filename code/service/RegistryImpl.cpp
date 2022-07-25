#include "RegistryImpl.h"

namespace svc {

RegistryImpl::RegistryImpl() {}
RegistryImpl::~RegistryImpl() {}

void RegistryImpl::registerService(ServiceList serviceNames, std::shared_ptr<IStandardWrapper> pWrapper) {
  for (ServiceList::iterator it = serviceNames.begin(); it != serviceNames.end(); ++it) {
    this->_standardMap[*it] = pWrapper;
  }
}

Status RegistryImpl::invoke(const std::string& serviceName, StandardPayload& payload) {
  // TODO: C++20 replace std::map::find() by std::map.contains()
  if (this->_standardMap.find(serviceName) == this->_standardMap.end()) {
    // service not found, return early
    // TODO: add error handling
    return Status(1, "service not found");
  }
  IStandardWrapper* pStandardWrapper = this->_standardMap[serviceName].get();
  std::shared_ptr<Service> pService = pStandardWrapper->createService();
  return pStandardWrapper->invoke(*pService, payload);
}

void RegistryImpl::registerService(ServiceList serviceNames, std::shared_ptr<ITokenWrapper> pWrapper) {
  for (ServiceList::iterator it = serviceNames.begin(); it != serviceNames.end(); ++it) {
    this->_tokenMap[*it] = pWrapper;
  }
}

Status RegistryImpl::invoke(const std::string& serviceName, TokenPayload& payload) {
  // TODO: C++20 replace std::map::find() by std::map.contains()
  if (this->_tokenMap.find(serviceName) == this->_tokenMap.end()) {
    // service not found, return early
    // TODO: add error handling
    return Status(1, "service not found");
  }
  ITokenWrapper* pTokenWrapper = this->_tokenMap[serviceName].get();
  std::shared_ptr<Service> pService = pTokenWrapper->createService();
  return pTokenWrapper->invoke(*pService, payload);
}

} // namespace svc