#include "serv_exceptions.h"

const char* SocketIdException::what() const noexcept {
  return "Error while creating socket";
}

const char* BindException::what() const noexcept {
  return "Error while binding socket to port 8080";
}

const char* ListenException::what() const noexcept {
  return "Error while executing listen method";
}

const char* AcceptException::what() const noexcept {
  return "Error while accepting incoming messages";
}

const char* SocketReadException::what() const noexcept {
  return "Error while reading from the socket";
}

const char* SocketSendException::what() const noexcept {
  return "Error while sending to the socket";
}