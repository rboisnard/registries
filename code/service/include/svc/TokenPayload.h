#ifndef _SVC_TOKEN_PAYLOAD_H
#define _SVC_TOKEN_PAYLOAD_H

#include <string>

namespace svc {

class TokenPayload {
public:
  explicit TokenPayload(const std::string data);
  explicit TokenPayload(const std::string data, std::string token);
  ~TokenPayload();

  const std::string data() const;
  std::string token() const;
  void setToken(std::string token);

  std::string serviceName();
  void setServiceName(std::string serviceName);

private:
  const std::string _data;
  std::string _token;
  std::string _serviceName;
};

} // namespace svc

#endif // _SVC_TOKEN_PAYLOAD_H