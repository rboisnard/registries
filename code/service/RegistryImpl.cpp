#include "RegistryImpl.h"

namespace svc {

RegistryImpl::RegistryImpl() {}
RegistryImpl::~RegistryImpl() {}

void RegistryImpl::registerCallback(ServiceList_t serviceNames, std::shared_ptr<ICallbackWrapper> pWrapper) {
  for (ServiceList_t::iterator it = serviceNames.begin(); it != serviceNames.end(); ++it) {
    this->_callbackMap[*it] = pWrapper;
  }
}

txn::Status RegistryImpl::invoke(const std::string& serviceName, Payload_t payload) {
  // TODO: C++20 replace std::map::find() by std::map.contains()
  if (this->_callbackMap.find(serviceName) == this->_callbackMap.end()) {
    // service not found, return early
    // TODO: add error handling
    return txn::Status(1, "service not found");
  }
  ICallbackWrapper* pCallbackWrapper = this->_callbackMap[serviceName].get();
  std::shared_ptr<Callback> pCallback = pCallbackWrapper->createCallback(std::make_shared<txn::Service>(*this));
  return pCallbackWrapper->invoke(*pCallback, payload);
}

} // namespace svc