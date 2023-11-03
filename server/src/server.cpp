#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <chrono>
#include <ctime>
#include <iostream>
#include <vector>

#include "serv_exceptions.h"

#define PORT_NO 20001

using namespace std;

int main() {
  int socket_fd, new_socekt_fd;

  struct sockaddr_in serv_addr, cli_addr;
  socklen_t cli_addr_size = sizeof(cli_addr);

  // for some time and date output
  auto time_now = chrono::system_clock::to_time_t(chrono::system_clock::now());
  bool end = false;
  vector<int> data;
  int num;
  char buffer[16];

  try {
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) throw SocketIdException();

    // ipv4
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    // changing from host byte order to network byte order
    serv_addr.sin_port = htons(PORT_NO);
    if (bind(socket_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      throw BindException();
    }
    // listen to conn requests on socket_fd, max 3 pending conns
    if (listen(socket_fd, 3) < 0) throw ListenException();
    cout << "Server is UP!" << endl;
    // when conn is accepted make new_socket_fd to use that file for actions
    // socket_fd stays for other incoming conns
    if ((new_socekt_fd = accept(socket_fd, (struct sockaddr*)&cli_addr,
                                &cli_addr_size)) < 0) {
      close(new_socekt_fd);
      throw AcceptException();
    }
    while (!end) {
      // read command
      if (read(new_socekt_fd, &num, sizeof(int)) < 0) {
        close(new_socekt_fd);
        throw SocketReadException();
      }
      switch (num) {
        case 0:  // close program, cmd 0
          cout << ctime(&time_now) << "| Closing program...";
          close(new_socekt_fd);
          end = true;
          break;
        case 1:  // push_back(), cmd 1
          // read number to be pushed back
          if (read(new_socekt_fd, &num, sizeof(int)) < 0) {
            close(new_socekt_fd);
            throw SocketReadException();
          }
          data.push_back(num);
          cout << ctime(&time_now) << "| Pushed " << num << " to the back"
               << endl;
          break;
        case 2:  // pop_back, cmd 2
          // if there are any data in vector
          if (data.size() > 0) {
            num = data.back();
            data.pop_back();
            // return popped data to client
            if (send(new_socekt_fd, &num, sizeof(int), 0) < 0) {
              close(new_socekt_fd);
              throw SocketSendException();
            }
            cout << ctime(&time_now) << "| Popped " << num << " from the back"
                 << endl;
          } else {
            num = -1;
            // return -1 to client if there is no data in vector
            if (send(new_socekt_fd, &num, sizeof(int), 0) < 0) {
              close(new_socekt_fd);
              throw SocketSendException();
            }
            cout << ctime(&time_now)
                 << "| Can't pop anything because vector is empty" << endl;
          }
          break;
        case 3:  // size, cmd 3
          num = data.size();
          // send size back to client
          if (send(new_socekt_fd, &num, sizeof(int), 0) < 0) {
            close(new_socekt_fd);
            throw SocketSendException();
          }
          cout << ctime(&time_now) << "| Sent size (" << num
               << ") to the client" << endl;
          break;
        case 4:  // clear, cmd 4
          data.clear();
          cout << ctime(&time_now) << "| Vector data cleared" << endl;
          break;
        default:  // unknown command, do not do anything
          cout << ctime(&time_now) << "| Unknown command" << endl;
          break;
      }
    }

  } catch (const exception& e) {
    // catch all exceptions
    cerr << e.what() << '\n';
    close(socket_fd);
    exit(1);
  }
  // close open socket
  close(socket_fd);
  return 0;
}