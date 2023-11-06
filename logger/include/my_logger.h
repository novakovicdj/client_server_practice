#ifndef _my_logger_h_
#define _my_logger_h_

#include <time.h>

#include <chrono>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

class MyLogger {
 private:
  static time_t time_now;
  ofstream f_out;
  ofstream f_err;

 public:
  MyLogger(string type_);

  void writeOutput(string msg);
  void writeError(string err);

  ~MyLogger();
};

#endif