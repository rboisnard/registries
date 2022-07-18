#ifndef _TXN_STATUS_H
#define _TXN_STATUS_H

#include <sstream>
#include <string>

namespace txn {

class Status {
public:
  explicit Status(int code);
  Status(int code, const std::string& message);
  ~Status();

  int code() const;
  std::string message() const;
  void setMessage(const std::string& message);
  void setMessage(const std::stringstream& message);
  operator bool() const;

  friend std::ostream& operator<<(std::ostream& os, const Status& status);

private:
  int _code;
  std::string _message;
};

} // namespace txn

#endif // _TXN_STATUS_H