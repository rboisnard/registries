#include <dlfcn.h>
#include <cstdlib>

#include "svc/Registry.h"
#include "RegistryImpl.h"
#include "TxnStandardPayloadAdapter.h"
#include "TxnStatusAdapter.h"
#include "TxnTokenPayloadAdapter.h"

namespace svc {

Registry::Registry() {
  _pImpl = std::shared_ptr<IRegistry>(new RegistryImpl());
}
Registry::~Registry() {}

txn::Status Registry::invoke(const std::string& serviceName, txn::StandardPayload& payload) {
  StandardPayload svcPayload = TxnStandardPayloadAdapter(payload);
  return TxnStatusAdapter(this->_pImpl->invoke(serviceName, svcPayload)).asTxnStatus();
}

txn::Status Registry::invoke(const std::string& serviceName, txn::TokenPayload& payload) {
  TokenPayload svcPayload = TxnTokenPayloadAdapter(payload);
  return TxnStatusAdapter(this->_pImpl->invoke(serviceName, svcPayload)).asTxnStatus();
}

void Registry::setTxnRegistry(txn::Registry txnRegistry) {
  this->_txnRegistry = txnRegistry;
}

// global unique instance
Registry registryInstance;

} // namespace svc

// global unique library
void* registryLibraryHandle;

extern "C"
bool initLibrary(txn::Registry& registry) {
  char* appLibraryName = std::getenv("APP_LIBRARY_NAME");
  if (!appLibraryName) {
    // env var not found
    return false;
  }

  char* appInitilizerName = std::getenv("APP_INITILIZER_NAME");
  if (!appInitilizerName) {
    // env var not found
    return false;
  }

  registryLibraryHandle = dlopen(appLibraryName, RTLD_NOW);
  if (!registryLibraryHandle) {
    // lib not found or missing dependencies
    return false;
  }
  // reset errors
  dlerror();

  svc::initializer_t initializer = (svc::initializer_t)dlsym(registryLibraryHandle, appInitilizerName);
  if (dlerror()) {
    dlclose(registryLibraryHandle);
    return false;
  }

  svc::registryInstance.setTxnRegistry(registry);
  return initializer(svc::registryInstance);
}

extern "C"
bool closeLibrary() {
  if (registryLibraryHandle) {
    char* appFinalizerName = std::getenv("APP_FINALIZER_NAME");
    if (!appFinalizerName) {
      // env var not found
      dlclose(registryLibraryHandle);
      return false;
    }

    svc::finalizer_t finalizer = (svc::finalizer_t)dlsym(registryLibraryHandle, appFinalizerName);
    if (dlerror()) {
      dlclose(registryLibraryHandle);
      return false;
    }

    bool status = finalizer();
    dlclose(registryLibraryHandle);
    return status;
  }
  return true;
}