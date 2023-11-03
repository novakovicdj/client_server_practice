#ifndef _cli_exceptions_h_
#define _cli_exceptions_h_

#include <exception>

using namespace std;

class SocketFdException : public exception {
 public:
  const char* what() const noexcept override;
};

class InvalidAddressException : public exception {
 public:
  const char* what() const noexcept override;
};

class ConnFailedException : public exception {
 public:
  const char* what() const noexcept override;
};

class SocketSendException : public exception {
 public:
  const char* what() const noexcept override;
};

class SocketReadException : public exception {
 public:
  const char* what() const noexcept override;
};

#endif