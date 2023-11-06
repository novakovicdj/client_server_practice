#include "my_logger.h"

#include <iostream>

time_t MyLogger::time_now =
    chrono::system_clock::to_time_t(chrono::system_clock::now());

MyLogger::MyLogger(string type_) {
  MyLogger::time_now =
      chrono::system_clock::to_time_t(chrono::system_clock::now());
  string s = "./logs/" + type_ + "_outputs.log";
  f_out.open(s, ios_base::app);
  f_out << ctime(&time_now) << "| Start" << endl;
  f_out << "____________________________________" << endl;
  s = "./logs/" + type_ + "_errors.log";
  f_err.open(s, ios_base::app);
  f_err << ctime(&time_now) << "| Start" << endl;
  f_err << "____________________________________" << endl;
}

MyLogger::~MyLogger() {
  MyLogger::time_now =
      chrono::system_clock::to_time_t(chrono::system_clock::now());
  f_out << "____________________________________" << endl;
  f_out << ctime(&time_now) << "| End" << endl;
  f_err << "____________________________________" << endl;
  f_err << ctime(&time_now) << "| End" << endl;
  f_out.close();
  f_err.close();
}

void MyLogger::writeOutput(string msg) {
  // cout << msg << endl;
  MyLogger::time_now =
      chrono::system_clock::to_time_t(chrono::system_clock::now());
  f_out << ctime(&time_now) << "| " << msg << endl;
}

void MyLogger::writeError(string err) {
  // cerr << err << endl;
  MyLogger::time_now =
      chrono::system_clock::to_time_t(chrono::system_clock::now());
  f_err << ctime(&time_now) << "| " << err << endl;
}