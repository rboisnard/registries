#ifndef _TXN_STANDARD_PAYLOAD_H
#define _TXN_STANDARD_PAYLOAD_H

#include <string>

namespace txn {

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

} // namespace txn

#endif // _TXN_STANDARD_PAYLOAD_H