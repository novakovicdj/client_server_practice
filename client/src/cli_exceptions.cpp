#include "cli_exceptions.h"

const char* SocketFdException::what() const noexcept {
  return "Error while creating socket";
}

const char* InvalidAddressException::what() const noexcept {
  return "Error while converting IP address";
}

const char* ConnFailedException::what() const noexcept {
  return "Error while trying to make a connection";
}

const char* SocketSendException::what() const noexcept {
  return "Error while sending data to socket";
}

const char* SocketReadException::what() const noexcept {
  return "Error while reading data from socket";
}