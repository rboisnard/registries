#include "txn/Status.h"

namespace txn {

Status::Status(int code)
    : Status(code, "") {}

Status::Status(int code, const std::string& message)
    : _code(code), _message(message) {}

Status::~Status() {}

int Status::code() const {
  return this->_code;
}

std::string Status::message() const {
  return this->_message;
}

void Status::setMessage(const std::string& message) {
  this->_message = message;
}

void Status::setMessage(const std::stringstream& message) {
  this->_message = message.str();
}

Status::operator bool() const {
  return (this->_code == 0);
}

std::ostream& operator<<(std::ostream& os, const Status& status) {
  os << status.message();
  return os;
}

} // namespace txn