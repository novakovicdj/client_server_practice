#ifndef _serv_exceptions_h_
#define _serv_exceptions_h_

#include <exception>

using namespace std;

class SocketIdException : public exception {
 public:
  const char* what() const noexcept override;
};

class BindException : public exception {
 public:
  const char* what() const noexcept override;
};

class ListenException : public exception {
 public:
  const char* what() const noexcept override;
};

class AcceptException : public exception {
 public:
  const char* what() const noexcept override;
};

class SocketReadException : public exception {
 public:
  const char* what() const noexcept override;
};

class SocketSendException : public exception {
 public:
  const char* what() const noexcept override;
};

#endif