#ifndef _SVC_STANDARD_PAYLOAD_H
#define _SVC_STANDARD_PAYLOAD_H

#include <string>

namespace svc {

class StandardPayload {
public:
  explicit StandardPayload(const std::string data);
  ~StandardPayload();

  const std::string data() const;

  std::string serviceName();
  void setServiceName(std::string serviceName);

private:
  const std::string _data;
  std::string _serviceName;
};

} // namespace svc

#endif // _SVC_STANDARD_PAYLOAD_H