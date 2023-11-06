#include "serv_exceptions.h"

#include "my_logger.h"

extern MyLogger my_logg;

const char* SocketIdException::what() const noexcept {
  my_logg.writeError("Error while creating socket");
  return "Error occured. Check the log file";
}

const char* BindException::what() const noexcept {
  my_logg.writeError("Error while binding socket to port 8080");
  return "Error occured. Check the log file";
}

const char* ListenException::what() const noexcept {
  my_logg.writeError("Error while executing listen method");
  return "Error occured. Check the log file";
}

const char* AcceptException::what() const noexcept {
  my_logg.writeError("Error while accepting incoming messages");
  return "Error occured. Check the log file";
}

const char* SocketReadException::what() const noexcept {
  my_logg.writeError("Error while reading from the socket");
  return "Error occured. Check the log file";
}

const char* SocketSendException::what() const noexcept {
  my_logg.writeError("Error while sending to the socket");
  return "Error occured. Check the log file";
}