#include "txn/Registry.h"
#include "RegistryImpl.h"

namespace txn {

Registry::Registry()
    : _pImpl(std::make_unique<RegistryImpl>()) {}
Registry::~Registry() {}

} // namespace txn