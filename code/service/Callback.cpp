#include "svc/Callback.h"

namespace svc {

Callback::Callback(std::shared_ptr<txn::Service> pService)
    : _pService(pService) {}

Callback::~Callback() {}

txn::Service& Callback::service() {
  return *(this->_pService.get());
}

} // namespace svc