#ifndef _SVC_CALLBACK_H
#define _SVC_CALLBACK_H

#include <memory>

#include "txn/Service.h"

namespace svc {

class Callback {
public:
  explicit Callback(std::shared_ptr<txn::Service> pService);
  ~Callback();

  txn::Service& service();

private:
  std::shared_ptr<txn::Service> _pService;
};

} // namespace svc

#endif // _SVC_CALLBACK_H