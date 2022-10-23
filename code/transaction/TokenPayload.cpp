#include "txn/TokenPayload.h"

namespace txn {

TokenPayload::TokenPayload(const std::string data)
    : TokenPayload(data, "") {}
TokenPayload::TokenPayload(const std::string data, std::string token)
    : _data(data), _token(token) {}
TokenPayload::~TokenPayload() {}

const std::string TokenPayload::data() const { return this->_data; }
std::string TokenPayload::token() const { return this->_token; }
void TokenPayload::setToken(std::string token) { this->_token = token; }

} // namespace txn