#ifndef _TXN_TOKEN_PAYLOAD_H
#define _TXN_TOKEN_PAYLOAD_H

#include <string>

namespace txn {

class TokenPayload {
public:
  explicit TokenPayload(const std::string data);
  explicit TokenPayload(const std::string data, std::string token);
  ~TokenPayload();

  const std::string data() const;
  std::string token();
  void setToken(std::string token);

private:
  const std::string _data;
  std::string _token;
};

} // namespace txn

#endif // _TXN_TOKEN_PAYLOAD_H