#include "cli_exceptions.h"

#include "my_logger.h"

extern MyLogger my_logg;

const char* SocketFdException::what() const noexcept {
  my_logg.writeError("Error while creating socket");
  return "Error occured. Check the log file";
}

const char* InvalidAddressException::what() const noexcept {
  my_logg.writeError("Error while converting IP address");
  return "Error occured. Check the log file";
}

const char* ConnFailedException::what() const noexcept {
  my_logg.writeError("Error while trying to make a connection");
  return "Error occured. Check the log file";
}

const char* SocketSendException::what() const noexcept {
  my_logg.writeError("Error while sending data to socket");
  return "Error occured. Check the log file";
}

const char* SocketReadException::what() const noexcept {
  my_logg.writeError("Error while reading data from socket");
  return "Error occured. Check the log file";
}