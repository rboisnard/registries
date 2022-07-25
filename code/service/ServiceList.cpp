#include "svc/ServiceList.h"

namespace svc {

ServiceList::ServiceList(std::initializer_list<std::string> serviceList)
    : _serviceList(serviceList) {}

} // namespace svc