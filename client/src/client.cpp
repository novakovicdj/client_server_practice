#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <chrono>
#include <ctime>
#include <iostream>

#include "cli_exceptions.h"

#define PORT_NO 20001

using namespace std;

int main() {
  int socket_fd;
  struct sockaddr_in serv_addr;
  // for date and time output
  auto time_now = chrono::system_clock::to_time_t(chrono::system_clock::now());
  bool end = false;
  int num;

  try {
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) throw SocketFdException();
    // socket of ipv4 and change port from host byte order to network byte order
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT_NO);
    // working on localhost so transform 127.0.0.1 to network bytes
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
      throw InvalidAddressException();
    }
    // connect to socket on server
    if (connect(socket_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) <
        0) {
      throw ConnFailedException();
    }
    while (!end) {
      cout << "\nEnter your command ( 0 - 4 ):" << endl;  // Menu for commands
      cout << "0 - exit" << endl << "1 - push_back()" << endl;
      cout << "2 - pop_back()" << endl
           << "3 - size()" << endl
           << "4 - clear()" << endl
           << "cmd: ";
      cin >> num;
      // send command
      if (send(socket_fd, &num, sizeof(num), 0) < 0) {
        throw SocketSendException();
      }
      // cout << "| Sent command " << num << endl;
      switch (num) {
        case 0:  // close program
          cout << ctime(&time_now) << "| Closing program...";
          end = true;
          break;
        case 1:
          cout << "Enter number: ";
          cin >> num;
          // send num to be pushed back
          if (send(socket_fd, &num, sizeof(num), 0) < 0) {
            throw SocketSendException();
          }
          cout << ctime(&time_now) << "| Pushed " << num << " to the back"
               << endl;
          break;
        case 2:  // pop back
          // wait for server to send popped data
          if (read(socket_fd, &num, sizeof(num)) < 0) {
            throw SocketReadException();
          }
          if (num != -1)  // -1 will be sent if there is no data
            cout << ctime(&time_now) << "| " << num << " popped from the back"
                 << endl;
          else
            cout << ctime(&time_now)
                 << "| Can't pop anything because vector is empty" << endl;
          break;
        case 3:  // size
          // wait for size to be sent from server
          if (read(socket_fd, &num, sizeof(num)) < 0) {
            throw SocketReadException();
          }
          cout << ctime(&time_now) << "| Size of the vector is " << num << endl;
          break;
        case 4:  // clear
          cout << ctime(&time_now) << "| Vector is cleared" << endl;
          break;
        default:  // unknown command
          cout << "Unknown command" << endl;
          break;
      }
    }

  } catch (const exception& e) {  // catch exceptions
    cerr << e.what() << '\n';
    close(socket_fd);
    exit(1);
  }
  // close open socket
  close(socket_fd);
  return 0;
}