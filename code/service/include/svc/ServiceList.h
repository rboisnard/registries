#ifndef _SVC_SERVICE_LIST_H
#define _SVC_SERVICE_LIST_H

#include <initializer_list>
#include <string>
#include <vector>

namespace svc {

class ServiceList {
public:
  using ServiceListType = std::vector<std::string>;
  typedef ServiceListType::iterator iterator;

  ServiceList(std::initializer_list<std::string> serviceList);

  inline ServiceListType::iterator begin() { return _serviceList.begin(); }
  inline ServiceListType::iterator end() { return _serviceList.end(); }

private:
  ServiceListType _serviceList;
};

} // namespace svc

#endif // _SVC_SERVICE_LIST_H