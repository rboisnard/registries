#ifndef _SVC_STATUS_H
#define _SVC_STATUS_H

#include <sstream>
#include <string>

namespace svc {

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

protected:
  int _code;
  std::string _message;
};

} // namespace svc

#endif // _SVC_STATUS_H